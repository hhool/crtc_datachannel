/* @Copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-02-08
 * @file libca_crtc_dc_unittest.cc
 */

// clang-format off
#include "tests/libca_crtc_dc_unittest.h"

#include <algorithm>
#include <thread>

#include "crtc_utils/libca_crtc_utils_sdp.h"

// clang-format on

#if defined(_WIN32)
#include <crtdbg.h>
#endif

namespace crtc {
namespace test {

enum {
  INVOKE_FOREVER = -1,
  INVOKE_TIMEOUT = 3000,
};

class CRtcDCAPITest::CPeerDatachannel
    : public crtc::CRTCPeerConnectionEventObserver {
 public:
  CPeerDatachannel(const std::string& name, CRtcDCAPITest* dc_api_test)
      : name_(name), dc_api_test_(dc_api_test) {
    Init();
  }
  virtual ~CPeerDatachannel() { DeInit(); }

 public:
  const std::string& name() const { return name_; }

 public:
  bool CreateOffer(std::string* sdp) {
    crtc_sdp_create_observer observer_sdp_create;
    pc_event_create_sdp_.reset(new CRTCCreateSessionDescriptEvent());
    pc_event_create_sdp_->Bind(&observer_sdp_create, this);

    crtc_rtc_offer_answer_options options;
    int32_t ret =
        crtc_pc_create_offer(handle_pc_, &observer_sdp_create, &options);
    EXPECT_EQ(ret, 0);
    if (ret != 0) {
      return false;
    }
    if (!pc_event_create_sdp_->Wait(INVOKE_FOREVER)) {
      return false;
    }
    if (!pc_event_create_sdp_->successed()) {
      return false;
    }
    *sdp = pc_event_create_sdp_->sdp();
    return true;
  }

  bool SetLocalDescription(crtc_e_sdp_type type, const std::string& sdp) {
    crtc_sdp_set_observer observer_sdp_set;
    pc_event_set_sdp_.reset(new CRTCSetSessionDescriptEvent());
    pc_event_set_sdp_->Bind(&observer_sdp_set, this);
    int32_t ret = crtc_pc_set_local_description(handle_pc_, &observer_sdp_set,
                                                type, sdp.c_str());
    EXPECT_EQ(ret, 0);
    if (ret != 0) {
      return false;
    }
    if (!pc_event_set_sdp_->Wait(INVOKE_FOREVER)) {
      return false;
    }
    if (!pc_event_set_sdp_->successed()) {
      return false;
    }
    return true;
  }

  bool SetRemoteDescription(crtc_e_sdp_type type, const std::string& sdp) {
    crtc_sdp_set_observer observer_sdp_set;
    pc_event_set_sdp_.reset(new CRTCSetSessionDescriptEvent());
    pc_event_set_sdp_->Bind(&observer_sdp_set, this);
    int32_t ret = crtc_pc_set_remote_description(handle_pc_, &observer_sdp_set,
                                                 type, sdp.c_str());
    EXPECT_EQ(ret, 0);
    if (ret != 0) {
      return false;
    }
    if (!pc_event_set_sdp_->Wait(INVOKE_FOREVER)) {
      return false;
    }
    if (!pc_event_set_sdp_->successed()) {
      return false;
    }
    remote_sdp_set_ = true;
    return true;
  }

  bool CreateAnswer(std::string* sdp) {
    crtc_sdp_create_observer observer_answer_sdp_create;
    pc_event_create_sdp_.reset(new CRTCCreateSessionDescriptEvent());
    pc_event_create_sdp_->Bind(&observer_answer_sdp_create, this);

    crtc_rtc_offer_answer_options options;
    int32_t ret = crtc_pc_create_answer(handle_pc_, &observer_answer_sdp_create,
                                        &options);
    EXPECT_EQ(ret, 0);
    if (ret != 0) {
      return false;
    }
    if (!pc_event_create_sdp_->Wait(INVOKE_FOREVER)) {
      return false;
    }
    if (!pc_event_create_sdp_->successed()) {
      return false;
    }
    *sdp = pc_event_create_sdp_->sdp();
    return true;
  }

  void AddCandidate(const CRTCandidate& candi) {
    if (remote_sdp_set_) {
      std::vector<std::unique_ptr<CRTCandidate>> candidates;
      size_t size;
      {
        std::unique_lock<std::mutex> mlock(std_mutex_);
        size = candidates_.size();
        for (size_t i = 0; i < size; ++i) {
          candidates.push_back(std::move(candidates_[i]));
        }
        candidates_.clear();
      }
      for (size_t i = 0; i < size; ++i) {
        int ret = crtc_pc_add_ice_candidate(
            handle_pc_, (*candidates[i]).mid().c_str(),
            (*candidates[i]).mline_index(),
            (*candidates[i]).candidate().c_str());
        EXPECT_EQ(ret, 0);
      }
      int ret = crtc_pc_add_ice_candidate(handle_pc_, candi.mid().c_str(),
                                          candi.mline_index(),
                                          candi.candidate().c_str());
      EXPECT_EQ(ret, 0);
    } else {
      std::unique_lock<std::mutex> mlock(std_mutex_);
      std::unique_ptr<CRTCandidate> candidate(new CRTCandidate(candi));
      candidates_.push_back(std::move(candidate));
    }
  }

 public:
  static HANDLE handle_crtc_;
  static HANDLE handle_pcf_;

 protected:
  int Init() {
    int ret = -1;
    do {
      remote_sdp_set_ = false;

      // create peer connection caller.
      crtc_rtc_configuration configure;
      memset(&configure, 0, sizeof(crtc_rtc_configuration));
      configure.sdp_semantics_ = kPlanB;
      configure.type_ = kAll;
      configure.enable_dtls_srtp_ = true;
      memset(configure.turn_uri_, 0, 1024);

      crtc_pc_observer pc_caller_observer;
      memset(&pc_caller_observer, 0, sizeof(crtc_pc_observer));
      pc_event_.reset(new CRTCPeerConnectionEvent(name_));
      pc_event_->Bind(&pc_caller_observer, this);
      int error = 0;
      handle_pc_ = crtc_pcf_create_peer_connection(handle_pcf_, &configure,
                                                   &pc_caller_observer, &error);
      EXPECT_TRUE(!!handle_pc_);
      if (handle_pc_ == NULL) {
        break;
      }

      // create data channel caller
      crtc_data_channel_init dc_init;
      dc_init.id = -1;
      dc_init.reliable = true;
      dc_init.ordered = true;
      dc_init.maxRetransmitTime = -1;
      dc_init.maxRetransmits = -1;
      dc_init.negotiated = false;
      std::string name_dc = std::string("dc_") + name_;
      handle_dc_ =
          crtc_pc_create_datachannel(handle_pc_, name_dc.c_str(), &dc_init);
      if (handle_dc_ == NULL) {
        break;
      }
      crtc_data_channel_event dc_observer;
      dc_event_->Bind(&dc_observer, this);
      crtc_dc_register_observer(handle_dc_, &dc_observer);
      ret = 0;
    } while (false);
    return ret;
  }
  void DeInit() {
    if (handle_dc_) {
      crtc_dc_close(handle_dc_);
      handle_dc_ = NULL;
    }
    if (handle_pc_) {
      crtc_pc_destroy(handle_pc_);
      handle_pc_ = NULL;
    }
  }
  // Inherited via CRTCPeerConnectionEventObserver
  void OnDataChannel(const CRTCPeerConnectionEventBase* pc_event_base,
                     CRTCDataChannelBase* data_channel) override {}

  void OnIceCandidate(const CRTCPeerConnectionEventBase* pc_event_base,
                      const CRTCandidate& candiate) override {
    dc_api_test_->OnCandidate(this, candiate);
  }

 private:
  std::string name_;
  HANDLE handle_pc_;
  HANDLE handle_dc_;
  std::unique_ptr<CRTCPeerConnectionEvent> pc_event_;
  std::unique_ptr<CRTCDataChannelEvent> dc_event_;
  std::unique_ptr<CRTCCreateSessionDescriptEvent> pc_event_create_sdp_;
  std::unique_ptr<CRTCSetSessionDescriptEvent> pc_event_set_sdp_;

 private:
  bool remote_sdp_set_;
  std::vector<std::unique_ptr<CRTCandidate>> candidates_;
  std::mutex std_mutex_;

 private:
  CRtcDCAPITest* dc_api_test_;
};

HANDLE CRtcDCAPITest::CPeerDatachannel::handle_crtc_ = nullptr;
HANDLE CRtcDCAPITest::CPeerDatachannel::handle_pcf_ = nullptr;

CRtcDCAPITest::CRtcDCAPITest()
    : handle_crtc_(NULL),
      handle_pcf_(NULL),
      data_channel_caller_in_(NULL),
      data_channel_called_in_(NULL) {
  crtc_debug(NULL, crtc_e_debug_log_level::kLogLevelVerbose);
}

CRtcDCAPITest::~CRtcDCAPITest() {}

void CRtcDCAPITest::Init() {
  do {
    handle_crtc_ = crtc_init(NULL);
    EXPECT_TRUE(!!handle_crtc_);
    if (handle_crtc_ == NULL) {
      break;
    }
    handle_pcf_ =
        crtc_create_peer_connection_factory(handle_crtc_, NULL, NULL, 0, NULL);
    EXPECT_TRUE(!!handle_pcf_);
    if (handle_pcf_ == NULL) {
      return;
    }
    CRtcDCAPITest::CPeerDatachannel::handle_crtc_ = handle_crtc_;
    CRtcDCAPITest::CPeerDatachannel::handle_pcf_ = handle_pcf_;

    peer_dc_caller_.reset(new CPeerDatachannel("caller", this));
    peer_dc_called_.reset(new CPeerDatachannel("called", this));
  } while (false);
}

void CRtcDCAPITest::ProcessSdp() {
  do {
    std::string offer_sdp;
    if (!peer_dc_caller_->CreateOffer(&offer_sdp)) {
      break;
    }

    if (!peer_dc_caller_->SetLocalDescription(crtc_e_sdp_type::kOffer,
                                              offer_sdp)) {
      break;
    }

    if (!peer_dc_called_->SetRemoteDescription(crtc_e_sdp_type::kOffer,
                                               offer_sdp)) {
      break;
    }

    std::string answer_sdp;
    if (!peer_dc_called_->CreateAnswer(&answer_sdp)) {
      break;
    }

    if (!peer_dc_called_->SetLocalDescription(crtc_e_sdp_type::kAnswer,
                                              answer_sdp)) {
      break;
    }

    if (!peer_dc_caller_->SetRemoteDescription(crtc_e_sdp_type::kAnswer,
                                               answer_sdp)) {
      break;
    }
  } while (false);
}

void CRtcDCAPITest::DeInit() {
  peer_dc_caller_.reset();
  peer_dc_called_.reset();
  if (handle_pcf_) {
    crtc_pcf_destroy(handle_pcf_);
    handle_pcf_ = NULL;
  }
  if (handle_crtc_) {
    crtc_deinit(handle_crtc_);
    handle_crtc_ = NULL;
  }
}

void CRtcDCAPITest::OnCandidate(const CPeerDatachannel* peer_dc,
                                const CRTCandidate& candi) {
  if (peer_dc == peer_dc_caller_.get()) {
    peer_dc_called_->AddCandidate(candi);
  } else {
    peer_dc_caller_->AddCandidate(candi);
  }
}

namespace {
static int32_t kMaxLoop = 2;
}
// --gtest_filter="CRtcDCAPITest.*"
// --gtest_filter="CRtcDCAPITest.Init_pcf_pc_ms_Destory"
TEST_F(CRtcDCAPITest, Init_pcf_pc_ms_Destory) {
  Init();
  ProcessSdp();
  std::this_thread::sleep_for(std::chrono::milliseconds(10000));
  DeInit();
}

// --gtest_filter="CRtcDCAPITest.Init_pcf_pc_ms_Destory_loop"
TEST_F(CRtcDCAPITest, Init_pcf_pc_ms_Destory_loop) {
  for (int i = 0; i < kMaxLoop; i++) {
    Init();
    ProcessSdp();
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    DeInit();
  }
}
}  // namespace test
}  // namespace crtc

