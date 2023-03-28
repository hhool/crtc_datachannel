/*
 * @Copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-03-06
 * @file libca_crtc_utils_sdp.cc
 */

// clang-format off
#include "crtc_utils/libca_crtc_utils_sdp.h"

#include <memory>
#include <vector>
#include <string>
// clang-format on

#ifndef LOG_INFO
#define LOG_INFO printf
#endif

namespace crtc {

static void split(const std::string& s,
                  const std::string& delim,
                  std::vector<std::string>* ret,
                  int limit = 0) {
  size_t last = 0;
  size_t index = s.find_first_of(delim, last);
  int limiting = 0;
  while (index != std::string::npos) {
    limiting++;
    if (limit > 0 && limiting >= (limit)) {
      index = s.length();
      break;
    }
    if ((index - last) > 0) {
      ret->push_back(s.substr(last, index - last));
    }
    last = index + delim.length();
    index = s.find_first_of(delim, last);
  }
  if (index != std::string::npos && (index - last) > 0) {
    ret->push_back(s.substr(last, index - last));
  }
}

std::string PreferCodec(const std::string& sdp,
                        const std::string& codec,
                        const bool isAudio) {
  std::vector<std::string> lines;

  std::string delim = "\r\n";
  split(sdp, delim, &lines, 0);

  std::string mediaDescription = "m=video ";
  if (isAudio) {
    mediaDescription = "m=audio ";
  }

  int mLineIndex = -1;
  std::string rtpMap;

  for (size_t i = 0;
       (i < lines.size()) && (mLineIndex == -1 || rtpMap.length() == 0); ++i) {
    if (lines[i].compare(0, mediaDescription.length(), mediaDescription) == 0) {
      mLineIndex = static_cast<int>(i);
      continue;
    }

    if (lines[i].compare(0, 8, "a=rtpmap") == 0) {
      std::vector<std::string> parts;
      split(lines[i], " ", &parts);
      if (parts.size() > 1) {
        if (parts[1].compare(0, codec.length(), codec) == 0) {
          std::vector<std::string> codes;
          split(parts[0], ":", &codes);
          if (codes.size() > 1) {
            rtpMap = codes[1];
          }
        }
      }
    }
  }

  if (mLineIndex == -1 || rtpMap.length() == 0) {
    return sdp;
  }

  std::string newSDP = "";

  std::vector<std::string> origMLineParts;
  split(lines[mLineIndex], " ", &origMLineParts);
  if (origMLineParts.size() < 3) {
    return sdp;
  }

  std::vector<std::string>::iterator it =
      std::find(origMLineParts.begin() + 2, origMLineParts.end(), rtpMap);
  if (it == origMLineParts.end()) {
    return sdp;
  }
  origMLineParts.erase(it);

  size_t origPartIndex = 0;
  std::string newMLine = "";
  // Format is: m=<media> <port> <proto> <fmt> ...
  newMLine.append(origMLineParts[origPartIndex++]).append(" ");
  newMLine.append(origMLineParts[origPartIndex++]).append(" ");
  newMLine.append(origMLineParts[origPartIndex++]).append(" ");
  newMLine.append(rtpMap).append(" ");

  for (; origPartIndex < origMLineParts.size(); ++origPartIndex) {
    if (origMLineParts[origPartIndex].compare(rtpMap)) {
      newMLine.append(origMLineParts[origPartIndex]);
      if (origPartIndex != origMLineParts.size() - 1)
        newMLine.append(" ");
    }
  }

  lines[mLineIndex] = newMLine;

  for (size_t i = 0; i < lines.size(); i++) {
    newSDP.append(lines[i]).append("\r\n");
  }

  return newSDP;
}

std::string PreferVideoCodecBitrate(const std::string& sdp,
                                    const std::string& codec,
                                    int32_t max_kbps,
                                    int32_t min_kbbs,
                                    int32_t start_kbps) {
  std::vector<std::string> lines;
  std::string delim = "\r\n";
  split(sdp, delim, &lines, 0);

  std::string mediaDescription = "m=video ";
  int mLineIndex = -1;
  std::string rtpMap;

  for (size_t i = 0;
       (i < lines.size()) && (mLineIndex == -1 || rtpMap.length() == 0); ++i) {
    if (lines[i].compare(0, mediaDescription.length(), mediaDescription) == 0) {
      mLineIndex = static_cast<int>(i);
      continue;
    }

    if (lines[i].compare(0, 8, "a=rtpmap") == 0) {
      std::vector<std::string> parts;
      split(lines[i], " ", &parts);
      if (parts.size() > 1) {
        if (parts[1].compare(0, codec.length(), codec) == 0) {
          std::vector<std::string> codes;
          split(parts[0], ":", &codes);
          if (codes.size() > 1) {
            rtpMap = codes[1];
          }
        }
      }
    }
  }

  if (mLineIndex == -1 || rtpMap.length() == 0) {
    return sdp;
  }

  mediaDescription.clear();
  mediaDescription = "a=fmtp:" + rtpMap + " ";
  rtpMap.clear();
  mLineIndex = -1;
  for (size_t i = 0; (i < lines.size()) && (mLineIndex == -1); ++i) {
    if (lines[i].compare(0, mediaDescription.length(), mediaDescription) != 0) {
      continue;
    } else {
      mLineIndex = static_cast<int>(i);
      break;
    }
  }
  if (mLineIndex == -1) {
    return sdp;
  }
  std::vector<std::string> origMLineParts;
  split(lines[mLineIndex].c_str() + mediaDescription.length(), ";",
        &origMLineParts);
  for (auto it = origMLineParts.begin(); it != origMLineParts.end();) {
    if ((*it).compare(0, std::strlen("x-google-max-bitrate"),
                      "x-google-max-bitrate") == 0) {
      it = origMLineParts.erase(it);
    } else if ((*it).compare(0, std::strlen("x-google-min-bitrate"),
                             "x-google-min-bitrate") == 0) {
      it = origMLineParts.erase(it);
    } else if ((*it).compare(0, std::strlen("x-google-start-bitrate"),
                             "x-google-start-bitrate") == 0) {
      it = origMLineParts.erase(it);
    } else {
      ++it;
    }
  }
  std::string value = "x-google-max-bitrate";
  value += "=";
  value += std::to_string(max_kbps);
  origMLineParts.push_back(value);

  value = "x-google-min-bitrate";
  value += "=";
  value += std::to_string(min_kbbs);
  origMLineParts.push_back(value);

  value = "x-google-start-bitrate";
  value += "=";
  value += std::to_string(start_kbps);
  origMLineParts.push_back(value);

  size_t origPartIndex = 0;
  std::string newMLine = mediaDescription;
  for (; origPartIndex < origMLineParts.size(); ++origPartIndex) {
    newMLine.append(origMLineParts[origPartIndex]);
    newMLine.append(";");
  }
  lines[mLineIndex] = newMLine;

  std::string newSDP = "";
  for (size_t i = 0; i < lines.size(); i++) {
    newSDP.append(lines[i]).append("\r\n");
  }

  return newSDP;
}

std::string PreferDisableRecv(const std::string& sdp) {
  std::string result = "";
  std::vector<std::string> lines;
  std::string delim = "\r\n";
  std::string ssrc_tag = "a=ssrc";
  split(sdp, delim, &lines, 0);

  for (size_t i = 0; i < lines.size(); i++) {
    if (lines[i].compare(0, ssrc_tag.length(), ssrc_tag) != 0) {
      result.append(lines[i]).append("\r\n");
    } else {
      LOG_INFO("remove sdp %s\n", lines[i].c_str());
    }
  }
  return result;
}

std::string PreferVideoBandWidth(const std::string& sdp, int nkbs) {
  std::string result;

  std::vector<std::string> lines;
  std::string delim = "\r\n";
  split(sdp, delim, &lines, 0);
  int mLineIndex = -1;
  for (size_t i = 0; i < lines.size(); ++i) {
    if (lines[i].compare(0, 8, "m=video ") == 0) {
      mLineIndex = static_cast<int>(i);
      break;
    }
  }

  int bitrate = nkbs;
  if (mLineIndex != -1) {
    lines.insert(lines.begin() + mLineIndex + 1,
                 "b=AS:" + std::to_string(bitrate));
  }

  for (size_t i = 0; i < lines.size(); i++) {
    result += lines[i] + "\r\n";
  }
  return result;
}

std::string PreferVideoBitrate(const std::string& sdp, int target_bitrate) {
  std::string result;

  std::vector<std::string> lines;
  std::string delim = "\r\n";
  split(sdp, delim, &lines, 0);
  int mLineIndex = -1;
  for (size_t i = 0; i < lines.size(); ++i) {
    if (lines[i].compare(0, 8, "m=video ") == 0) {
      mLineIndex = static_cast<int>(i);
      break;
    }
  }

  int bitrate = target_bitrate;
  if (mLineIndex != -1) {
    lines.insert(lines.begin() + mLineIndex + 1,
                 "b=AS:" + std::to_string(bitrate));
  }

  for (size_t i = 0; i < lines.size(); i++) {
    result += lines[i] + "\r\n";
  }
  return result;
}
}  // namespace crtc
