/* @Copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-03-20
 * @file libca_crtc_dc_unittest.h
 */

#ifndef CRTC_CRTC_API_UNITTEST_LIBCA_CRTC_DC_UNITTEST_H_
#define CRTC_CRTC_API_UNITTEST_LIBCA_CRTC_DC_UNITTEST_H_

// clang-format off
#include <libca_crtc_api.h>

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "crtc_utils/libca_crtc_utils_api.h"
#include <gtest/gtest.h>
// clang-format on

namespace crtc {
namespace test {

class CRtcDCAPITest : public ::testing::Test {
 public:
  CRtcDCAPITest();
  ~CRtcDCAPITest() override;

  class CPeerDatachannel;

 public:
  void Init();
  void ProcessSdp();
  void DeInit();

 protected:
  void OnCandidate(const CPeerDatachannel* peer_dc, const CRTCandidate& candi);

 protected:
  HANDLE handle_crtc_;
  HANDLE handle_pcf_;
  std::unique_ptr<CPeerDatachannel> peer_dc_caller_;
  std::unique_ptr<CPeerDatachannel> peer_dc_called_;
  CRTCDataChannelBase* data_channel_caller_in_;
  CRTCDataChannelBase* data_channel_called_in_;
};
}  // namespace test
}  // namespace crtc
#endif  // CRTC_CRTC_API_UNITTEST_LIBCA_CRTC_DC_UNITTEST_H_
