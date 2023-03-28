/*
 * @Copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-03-21
 * @file libca_crtc_api_utils.cc
 */

// clang-format off
#include "crtc_utils/libca_crtc_api_utils.h"
#include "crtc_utils/libca_crtc_utils_log.h"
// clang-format on

#ifndef LOG_INFO
#define LOG_INFO printf
#endif

namespace crtc {
///////////////////////////////////////////////////////////////////////////////
// clz CRTCandidate
CRTCandidate::CRTCandidate() : sdp_mline_index_(-1) {}

CRTCandidate::CRTCandidate(const std::string& mid,
                           int mline_index,
                           const std::string& candi)
    : sdp_mid_(mid), sdp_mline_index_(mline_index), candidate_(candi) {}

CRTCandidate::~CRTCandidate() {}

bool CRTCandidate::FromHandle(HANDLE handle, CRTCandidate* candi) {
  std::string candidate;
  std::string sdp_mid;
  int sdp_mline_index = -1;
  {
    int length = 0;
    int ret = crtc_jsep_ic_to_string(handle, NULL, &length);
    if (ret != 0) {
      return false;
    }
    if (length <= 0) {
      return false;
    }
    char* buffer = reinterpret_cast<char*>(malloc(sizeof(char) * (length + 1)));
    memset(buffer, 0, length + 1);
    ret = crtc_jsep_ic_to_string(handle, buffer, &length);
    if (ret != 0) {
      free(buffer);
      return false;
    }
    candidate = std::string(buffer, length);
    free(buffer);
  }
  {
    int length = 0;
    int ret = crtc_jsep_ic_get_sdp_mid(handle, NULL, &length);
    if (ret != 0) {
      return false;
    }
    if (length <= 0) {
      return false;
    }
    char* buffer = reinterpret_cast<char*>(malloc(sizeof(char) * (length + 1)));
    memset(buffer, 0, length + 1);
    ret = crtc_jsep_ic_get_sdp_mid(handle, buffer, &length);
    if (ret != 0) {
      free(buffer);
      return false;
    }
    sdp_mid = std::string(buffer, length);
    free(buffer);
  }
  {
    int ret = crtc_jsep_ic_get_sdp_mline_index(handle, &sdp_mline_index);
    if (ret != 0) {
      return false;
    }
  }
  *candi = CRTCandidate(sdp_mid, sdp_mline_index, candidate);
  return true;
}

const std::string& CRTCandidate::mid() const {
  return sdp_mid_;
}

int CRTCandidate::mline_index() const {
  return sdp_mline_index_;
}

const std::string& CRTCandidate::candidate() const {
  return candidate_;
}

///////////////////////////////////////////////////////////////////////////////
// clz CRTCPeerConnectionEventBase
CRTCPeerConnectionEventBase::CRTCPeerConnectionEventBase(
    const std::string& name)
    : name_(name) {}

CRTCPeerConnectionEventBase::~CRTCPeerConnectionEventBase() {}

const std::string& CRTCPeerConnectionEventBase::name() const {
  return name_;
}

///////////////////////////////////////////////////////////////////////////////
// clz CRTCDataChannelBase
CRTCDataChannelBase::~CRTCDataChannelBase() {}
///////////////////////////////////////////////////////////////////////////////
// clz CRTCDataChannelEventObserver
CRTCDataChannelEventObserver::~CRTCDataChannelEventObserver() {}
///////////////////////////////////////////////////////////////////////////////
// clz CRTCPeerConnectionEventObserver
CRTCPeerConnectionEventObserver::~CRTCPeerConnectionEventObserver() {}
///////////////////////////////////////////////////////////////////////////////
// clz CRTCPeerConnectionEvent
CRTCPeerConnectionEvent::CRTCPeerConnectionEvent(const std::string& name)
    : CRTCPeerConnectionEventBase(name), pc_event_observer_(nullptr) {}

CRTCPeerConnectionEvent::~CRTCPeerConnectionEvent() {}

crtc_pc_observer* CRTCPeerConnectionEvent::Bind(
    crtc_pc_observer* observer,
    crtc::CRTCPeerConnectionEventObserver* pc_event_observer) {
  pc_event_observer_ = pc_event_observer;
  observer->OnSignalingChange_ =
      CRTCPeerConnectionEvent::Event_OnSignalingChange;
  observer->OnAddStream_ = CRTCPeerConnectionEvent::Event_OnAddStream;
  observer->OnRemoveStream_ = CRTCPeerConnectionEvent::Event_OnRemoveStream;
  observer->OnDataChannel_ = CRTCPeerConnectionEvent::Event_OnDataChannel;
  observer->OnRenegotiationNeeded_ =
      CRTCPeerConnectionEvent::Event_OnRenegotiationNeeded;
  observer->OnIceConnectionChange_ =
      CRTCPeerConnectionEvent::Event_OnIceConnectionChange;
  observer->OnStandardizedIceConnectionChange_ =
      CRTCPeerConnectionEvent::Event_OnStandardizedIceConnectionChange;
  observer->OnConnectionChange_ =
      CRTCPeerConnectionEvent::Event_OnConnectionChange;
  observer->OnIceGatheringChange_ =
      CRTCPeerConnectionEvent::Event_OnIceGatheringChange;
  observer->OnIceCandidate_ = CRTCPeerConnectionEvent::Event_OnIceCandidate;
  observer->OnIceCandidatesRemoved_ =
      CRTCPeerConnectionEvent::Event_OnIceCandidatesRemoved;
  observer->OnIceConnectionReceivingChange_ =
      CRTCPeerConnectionEvent::Event_OnIceConnectionReceivingChange;
  observer->OnAddTrack_ = CRTCPeerConnectionEvent::Event_OnAddTrack;
  observer->OnTrack_ = CRTCPeerConnectionEvent::Event_OnTrack;
  observer->OnRemoveTrack_ = CRTCPeerConnectionEvent::Event_OnRemoveTrack;
  observer->OnInterestingUsage_ =
      CRTCPeerConnectionEvent::Event_OnInterestingUsage;
  observer->context_ = this;
  return observer;
}

void CRTCPeerConnectionEvent::CRTCPeerConnectionEvent::Event_OnSignalingChange(
    crtc_e_signaling_state new_state,
    void* context) {
  CRTCPeerConnectionEvent* p_this =
      reinterpret_cast<CRTCPeerConnectionEvent*>(context);
  LOG_INFO("name: %s , new_sate %d\n", p_this->name().c_str(), new_state);
}

void CRTCPeerConnectionEvent::Event_OnAddStream(HANDLE handle_ms,
                                                void* context) {
  CRTCPeerConnectionEvent* p_this =
      reinterpret_cast<CRTCPeerConnectionEvent*>(context);
  LOG_INFO("name: %s , handle_ms %p\n", p_this->name().c_str(), handle_ms);
}

void CRTCPeerConnectionEvent::Event_OnRemoveStream(HANDLE handle_ms,
                                                   void* context) {
  CRTCPeerConnectionEvent* p_this =
      reinterpret_cast<CRTCPeerConnectionEvent*>(context);
  LOG_INFO("name: %s , handle_ms %p\n", p_this->name().c_str(), handle_ms);
}

void CRTCPeerConnectionEvent::Event_OnDataChannel(HANDLE handle_dc,
                                                  void* context) {
  CRTCPeerConnectionEvent* p_this =
      reinterpret_cast<CRTCPeerConnectionEvent*>(context);
  LOG_INFO("name: %s , handle_ms %p\n", p_this->name().c_str(), handle_dc);
  CRTCDataChannel data_channel;
  CRTCDataChannel::FromHandle(handle_dc, &data_channel);
  p_this->pc_event_observer_->OnDataChannel(p_this, &data_channel);
}

void CRTCPeerConnectionEvent::Event_OnRenegotiationNeeded(void* context) {
  CRTCPeerConnectionEvent* p_this =
      reinterpret_cast<CRTCPeerConnectionEvent*>(context);
  LOG_INFO("name: %s\n", p_this->name().c_str());
}

void CRTCPeerConnectionEvent::Event_OnIceConnectionChange(
    crtc_e_ice_connection_state new_state,
    void* context) {
  CRTCPeerConnectionEvent* p_this =
      reinterpret_cast<CRTCPeerConnectionEvent*>(context);
  LOG_INFO("name: %s , new_sate %d\n", p_this->name().c_str(), new_state);
}

void CRTCPeerConnectionEvent::Event_OnStandardizedIceConnectionChange(
    crtc_e_ice_connection_state new_state,
    void* context) {
  CRTCPeerConnectionEvent* p_this =
      reinterpret_cast<CRTCPeerConnectionEvent*>(context);
  LOG_INFO("name: %s , new_sate %d\n", p_this->name().c_str(), new_state);
}

void CRTCPeerConnectionEvent::Event_OnConnectionChange(
    crtc_e_peer_connecion_state new_state,
    void* context) {
  CRTCPeerConnectionEvent* p_this =
      reinterpret_cast<CRTCPeerConnectionEvent*>(context);
  LOG_INFO("name: %s , new_sate %d\n", p_this->name().c_str(), new_state);
}

void CRTCPeerConnectionEvent::Event_OnIceGatheringChange(
    crtc_e_ice_gathering_state new_state,
    void* context) {
  CRTCPeerConnectionEvent* p_this =
      reinterpret_cast<CRTCPeerConnectionEvent*>(context);
  LOG_INFO("name: %s , new_sate %d\n", p_this->name().c_str(), new_state);
}

void CRTCPeerConnectionEvent::Event_OnIceCandidate(
    const HANDLE handle_ice_candidate,
    void* context) {
  CRTCPeerConnectionEvent* p_this =
      reinterpret_cast<CRTCPeerConnectionEvent*>(context);
  LOG_INFO("name: %s , handle_ice_candidate %p\n", p_this->name().c_str(),
           handle_ice_candidate);
  CRTCandidate candi;
  CRTCandidate::FromHandle(handle_ice_candidate, &candi);
  p_this->pc_event_observer_->OnIceCandidate(p_this, candi);
}

void CRTCPeerConnectionEvent::Event_OnIceCandidatesRemoved(void* context) {
  CRTCPeerConnectionEvent* p_this =
      reinterpret_cast<CRTCPeerConnectionEvent*>(context);
  LOG_INFO("name: %s\n", p_this->name().c_str());
}

void CRTCPeerConnectionEvent::Event_OnIceConnectionReceivingChange(
    bool receiving,
    void* context) {
  CRTCPeerConnectionEvent* p_this =
      reinterpret_cast<CRTCPeerConnectionEvent*>(context);
  LOG_INFO("name: %s, receiving %d\n", p_this->name().c_str(), receiving);
}

void CRTCPeerConnectionEvent::Event_OnAddTrack(HANDLE handle_rtp_receiver,
                                               const HANDLE handle_ms_list[],
                                               int size,
                                               void* context) {
  CRTCPeerConnectionEvent* p_this =
      reinterpret_cast<CRTCPeerConnectionEvent*>(context);
  LOG_INFO("name: %s, handle_rtp_receiver %p\n", p_this->name().c_str(),
           handle_rtp_receiver);
  std::shared_ptr<CRTCRTPReceiver> rtp_receiver(
      new CRTCRTPReceiver(handle_rtp_receiver));
  p_this->pc_event_observer_->OnAddTrack(p_this, rtp_receiver);
}

void CRTCPeerConnectionEvent::Event_OnTrack(HANDLE handle_rtp_transceiver,
                                            void* context) {
  CRTCPeerConnectionEvent* p_this =
      reinterpret_cast<CRTCPeerConnectionEvent*>(context);
  LOG_INFO("name: %s, handle_rtp_transceiver %p\n", p_this->name().c_str(),
           handle_rtp_transceiver);
}

void CRTCPeerConnectionEvent::Event_OnRemoveTrack(HANDLE handle_rtp_reciver,
                                                  void* context) {
  CRTCPeerConnectionEvent* p_this =
      reinterpret_cast<CRTCPeerConnectionEvent*>(context);
  LOG_INFO("name: %s, handle_rtp_reciver %p\n", p_this->name().c_str(),
           handle_rtp_reciver);
}

void CRTCPeerConnectionEvent::Event_OnInterestingUsage(int usage_pattern,
                                                       void* context) {
  CRTCPeerConnectionEvent* p_this =
      reinterpret_cast<CRTCPeerConnectionEvent*>(context);
  LOG_INFO("name: %s, usage_pattern %d\n", p_this->name().c_str(),
           usage_pattern);
}

///////////////////////////////////////////////////////////////////////////////
// clz CRTCDataChannel
CRTCDataChannel::CRTCDataChannel() {}

CRTCDataChannel::~CRTCDataChannel() {}

bool CRTCDataChannel::FromHandle(HANDLE handle, CRTCDataChannel* channel) {
  // TODO(hhool):
  return false;
}

///////////////////////////////////////////////////////////////////////////////
// clz CRTCCreateSessionDescriptEventBase
CRTCCreateSessionDescriptEventBase::~CRTCCreateSessionDescriptEventBase() {}

///////////////////////////////////////////////////////////////////////////////
// clz CRTCSetSessionDescriptEventBase
CRTCSetSessionDescriptEventBase::~CRTCSetSessionDescriptEventBase() {}

///////////////////////////////////////////////////////////////////////////////
// clz CRTCDataChannelEventBase
CRTCDataChannelEventBase::~CRTCDataChannelEventBase() {}
///////////////////////////////////////////////////////////////////////////////
// clz CRTCCreateSessionDescriptEvent
CRTCCreateSessionDescriptEvent::CRTCCreateSessionDescriptEvent()
    : context_(nullptr), processed_(false), success_(false) {}

CRTCCreateSessionDescriptEvent::~CRTCCreateSessionDescriptEvent() {}

crtc_sdp_create_observer* CRTCCreateSessionDescriptEvent::Bind(
    crtc_sdp_create_observer* observer,
    void* context) {
  context_ = context;
  processed_ = false;
  observer->Context_ = this;
  observer->OnSuccess_ =
      CRTCCreateSessionDescriptEvent::OnEventSdpCreateOnSuccess;
  observer->OnFailed_ =
      CRTCCreateSessionDescriptEvent::OnEventSdpCreateOnFailed;
  return observer;
}

bool CRTCCreateSessionDescriptEvent::Wait(int give_up_after_ms) {
  std::unique_lock<std::mutex> mlock(std_mutex_);
  if (processed_) {
    return true;
  }
  if (give_up_after_ms < 0) {
    std_cond_var.wait(mlock);
    return true;
  }
  return (std_cond_var.wait_for(mlock,
                                std::chrono::milliseconds(give_up_after_ms)) !=
          std::cv_status::timeout);
}

bool CRTCCreateSessionDescriptEvent::successed() const {
  return success_;
}

const std::string& CRTCCreateSessionDescriptEvent::sdp() const {
  return sdp_;
}

void CRTCCreateSessionDescriptEvent::OnEventSdpCreateOnSuccess(
    const char* sdp_desc,
    int length,
    void* context) {
  CRTCCreateSessionDescriptEvent* p_this =
      reinterpret_cast<CRTCCreateSessionDescriptEvent*>(context);
  std::unique_lock<std::mutex> mlock(p_this->std_mutex_);
  p_this->sdp_ = std::string(sdp_desc, length);
  p_this->success_ = true;
  p_this->processed_ = true;
  p_this->std_cond_var.notify_one();
}

void CRTCCreateSessionDescriptEvent::OnEventSdpCreateOnFailed(int error,
                                                              void* context) {
  CRTCCreateSessionDescriptEvent* p_this =
      reinterpret_cast<CRTCCreateSessionDescriptEvent*>(context);
  std::unique_lock<std::mutex> mlock(p_this->std_mutex_);
  p_this->success_ = false;
  p_this->processed_ = true;
  p_this->std_cond_var.notify_one();
}
///////////////////////////////////////////////////////////////////////////////
// clz CRTCSetSessionDescriptEvent
CRTCSetSessionDescriptEvent::CRTCSetSessionDescriptEvent()
    : context_(nullptr), processed_(false), success_(false) {}

CRTCSetSessionDescriptEvent::~CRTCSetSessionDescriptEvent() {}

crtc_sdp_set_observer* CRTCSetSessionDescriptEvent::Bind(
    crtc_sdp_set_observer* observer,
    void* context) {
  context_ = context;
  processed_ = false;
  observer->Context_ = this;
  observer->OnSuccess_ = CRTCSetSessionDescriptEvent::OnEventSdpSetOnSuccess;
  observer->OnFailed_ = CRTCSetSessionDescriptEvent::OnEventSdpSetOnFailed;
  return observer;
}

bool CRTCSetSessionDescriptEvent::Wait(int give_up_after_ms) {
  std::unique_lock<std::mutex> mlock(std_mutex_);
  if (processed_) {
    return true;
  }
  if (give_up_after_ms < 0) {
    std_cond_var.wait(mlock);
    return true;
  }
  return (std_cond_var.wait_for(mlock,
                                std::chrono::milliseconds(give_up_after_ms)) !=
          std::cv_status::timeout);
}

bool CRTCSetSessionDescriptEvent::successed() const {
  return success_;
}

void CRTCSetSessionDescriptEvent::OnEventSdpSetOnSuccess(void* context) {
  CRTCSetSessionDescriptEvent* p_this =
      reinterpret_cast<CRTCSetSessionDescriptEvent*>(context);
  std::unique_lock<std::mutex> mlock(p_this->std_mutex_);
  p_this->processed_ = true;
  p_this->success_ = true;
  p_this->std_cond_var.notify_one();
}

void CRTCSetSessionDescriptEvent::OnEventSdpSetOnFailed(int error,
                                                        void* context) {
  CRTCSetSessionDescriptEvent* p_this =
      reinterpret_cast<CRTCSetSessionDescriptEvent*>(context);
  std::unique_lock<std::mutex> mlock(p_this->std_mutex_);
  p_this->processed_ = true;
  p_this->success_ = false;
  p_this->std_cond_var.notify_one();
}

///////////////////////////////////////////////////////////////////////////////
// clz CRTCDataChannelEvent
CRTCDataChannelEvent::CRTCDataChannelEvent() : context_(nullptr) {}

CRTCDataChannelEvent::~CRTCDataChannelEvent() {}

crtc_data_channel_event* CRTCDataChannelEvent::Bind(
    crtc_data_channel_event* observer,
    void* context) {
  observer->OnStateChange_ = Event_OnStateChange;
  observer->OnMessage_ = Event_OnMessage;
  observer->OnBufferedAmountChange_ = Event_OnBufferedAmountChange;
  return observer;
}

void CRTCDataChannelEvent::Event_OnStateChange() {}

void CRTCDataChannelEvent::Event_OnMessage(const uint8_t* buffer,
                                           int length,
                                           bool is_binary) {}
// The data channel's BufferedAmount has changed.
void CRTCDataChannelEvent::Event_OnBufferedAmountChange(
    uint64_t previous_amount) {}

///////////////////////////////////////////////////////////////////////////////
// clz CRTCStatsEventObserver
CRTCStatsEventObserver::~CRTCStatsEventObserver() {}
///////////////////////////////////////////////////////////////////////////////
// clz CRTCStatsEvent
CRTCStatsEvent::CRTCStatsEvent() {}

crtc_stats_observer* CRTCStatsEvent::Bind(
    crtc_stats_observer* observer,
    CRTCStatsEventObserver* event_observer) {
  event_observer_ = event_observer;
  observer->Callback_ = CRTCStatsEvent::StatsResultCallback;
  observer->Context_ = this;
  return observer;
}

void CRTCStatsEvent::StatsResultCallback(const char* json,
                                         int length,
                                         void* context) {
  CRTCStatsEvent* p_this = reinterpret_cast<CRTCStatsEvent*>(context);
  LOG_INFO("context: %s, context %p\n", json, context);
  p_this->event_observer_->OnStats(p_this, std::string(json, length));
}
///////////////////////////////////////////////////////////////////////////////
// clz CRTCVideoFrameRender
CRTCVideoFrameRender::CRTCVideoFrameRender(HANDLE context, int type)
    : context_(context), type_(type) {
  LOG_INFO("context: %p, type %d\n", context_, type);
}

CRTCVideoFrameRender::~CRTCVideoFrameRender() {}

crtc_video_sink* CRTCVideoFrameRender::Bind(crtc_video_sink* sink,
                                            void* context) {
  sink->OnFrame_ = CRTCVideoFrameRender::OnFrame;
  sink->Context_ = context;
  return sink;
}

void CRTCVideoFrameRender::OnFrame(const uint8_t* y,
                                   int stride_y,
                                   const uint8_t* u,
                                   int stride_u,
                                   const uint8_t* v,
                                   int stride_v,
                                   int width,
                                   int height,
                                   HANDLE context) {
  CRTCVideoFrameRender* render = static_cast<CRTCVideoFrameRender*>(context);
  if (render->type_ == CRTCVideoFrameRender::LOCAL) {
    LOG_INFO("local\n");
  } else {
    LOG_INFO("remote\n");
  }
}
///////////////////////////////////////////////////////////////////////////////
// clz CRTCRTPReceiver
CRTCRTPReceiver::CRTCRTPReceiver(HANDLE handle_rtp_receiver)
    : handle_rtp_receiver_(handle_rtp_receiver) {
  crtc_rr_get_media_type(handle_rtp_receiver_,
                         reinterpret_cast<int*>(&media_type_));
  HANDLE handle_mst;
  int ret = crtc_rr_get_track(handle_rtp_receiver, &handle_mst);
  if (ret == 0) {
    if (media_type_ == crtc_media_type::MEDIA_TYPE_VIDEO) {
      track_ = std::make_shared<CRTCMediaStreamVideoTrack>(handle_mst);
    } else if (media_type_ == crtc_media_type::MEDIA_TYPE_AUDIO) {
      track_ = std::make_shared<CRTCMediaStreamAudioTrack>(handle_mst);
    } else {
      LOG_INFO("unknown media type\n");
    }
  }
}

CRTCRTPReceiver::~CRTCRTPReceiver() {}

HANDLE CRTCRTPReceiver::native_handle() {
  return handle_rtp_receiver_;
}

crtc_media_type CRTCRTPReceiver::GetMediaType() const {
  return media_type_;
}

CRTCMediaStreamTrack* CRTCRTPReceiver::GetMediaStreamTrack() const {
  return track_.get();
}

///////////////////////////////////////////////////////////////////////////////
// clz CRTCMediaStreamTrack
CRTCMediaStreamTrack::CRTCMediaStreamTrack(HANDLE handle_mst)
    : handle_mst_(handle_mst) {}

CRTCMediaStreamTrack::~CRTCMediaStreamTrack() {
  if (handle_mst_ != nullptr) {
    crtc_vt_destroy(handle_mst_);
    handle_mst_ = nullptr;
  }
}

///////////////////////////////////////////////////////////////////////////////
// clz CRTCMediaStreamVideoTrack
CRTCMediaStreamVideoTrack::CRTCMediaStreamVideoTrack(HANDLE handle_mst)
    : CRTCMediaStreamTrack(handle_mst) {}

CRTCMediaStreamVideoTrack::~CRTCMediaStreamVideoTrack() {}

void CRTCMediaStreamVideoTrack::AddOrUpdateSink(
    HANDLE handle_vsr,
    const crtc_video_sink_wants* wants) {
  crtc_vt_add_or_update_sink(handle_mst_, handle_vsr, wants);
}

void CRTCMediaStreamVideoTrack::RemoveSink(HANDLE handle_vsr) {
  crtc_vt_remove_sink(handle_mst_, handle_vsr);
}

///////////////////////////////////////////////////////////////////////////////
// clz CRTCMediaStreamAudioTrack
CRTCMediaStreamAudioTrack::CRTCMediaStreamAudioTrack(HANDLE handle_mst)
    : CRTCMediaStreamTrack(handle_mst) {}
CRTCMediaStreamAudioTrack::~CRTCMediaStreamAudioTrack() {}
}  // namespace crtc
