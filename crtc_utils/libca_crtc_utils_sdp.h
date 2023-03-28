/*
 * @Copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-03-06
 * @file libca_crtc_utils_sdp.h
 */
#ifndef CRTC_CRTC_UTILS_LIBCA_CRTC_UTILS_SDP_H_
#define CRTC_CRTC_UTILS_LIBCA_CRTC_UTILS_SDP_H_

// clang-format off
#include <string>
// clang-format on

namespace crtc {
std::string PreferCodec(const std::string& sdp,
                        const std::string& codec,
                        const bool isAudio);
std::string PreferVideoCodecBitrate(const std::string& sdp,
                                    const std::string& codec,
                                    int32_t max_kbps,
                                    int32_t min_kbbs,
                                    int32_t start_kbps);
std::string PreferVideoBitrate(const std::string& sdp, int target_bitrate);
std::string PreferVideoBandWidth(const std::string& sdp, int nkbs);
std::string PreferDisableRecv(const std::string& sdp);
}  // namespace crtc
#endif  // CRTC_CRTC_UTILS_LIBCA_CRTC_UTILS_SDP_H_
