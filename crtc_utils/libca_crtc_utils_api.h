/*
 * @Copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-03-21
 * @file libca_crtc_utils_api.h
 */

#ifndef CRTC_CRTC_UTILS_LIBCA_CRTC_UTILS_API_H_
#define CRTC_CRTC_UTILS_LIBCA_CRTC_UTILS_API_H_

// clang-format off
#include <libca_crtc_api.h>

#include <condition_variable>
#include <memory>
#include <mutex>
#include <string>
// clang-format on

namespace crtc {
class CRTCandidate {
 public:
  CRTCandidate();
  CRTCandidate(const std::string& mid,
               int mline_index,
               const std::string& candi);
  virtual ~CRTCandidate();

  static bool FromHandle(HANDLE handle, CRTCandidate* candi);

 public:
  const std::string& mid() const;
  int mline_index() const;
  const std::string& candidate() const;

 private:
  std::string sdp_mid_;
  int sdp_mline_index_;
  std::string candidate_;
};

class CRTCPeerConnectionEventBase {
 public:
  explicit CRTCPeerConnectionEventBase(const std::string& name);
  virtual ~CRTCPeerConnectionEventBase();

 public:
  const std::string& name() const;

 private:
  std::string name_;
};

class CRTCDataChannelBase {
 public:
  virtual ~CRTCDataChannelBase();
};

class CRTCDataChannelEventObserver {
 public:
  virtual ~CRTCDataChannelEventObserver();
};

class CRTCMediaStreamTrack;
class CRTCRTPReceiver;
class CRTCPeerConnectionEventObserver {
 public:
  virtual ~CRTCPeerConnectionEventObserver();

 public:
  virtual void OnDataChannel(const CRTCPeerConnectionEventBase* pc_event_base,
                             CRTCDataChannelBase* data_channel) = 0;
  virtual void OnIceCandidate(const CRTCPeerConnectionEventBase* pc_event_base,
                              const CRTCandidate& candiate) = 0;
  virtual void OnAddTrack(const CRTCPeerConnectionEventBase* pc_event_base,
                          std::shared_ptr<CRTCRTPReceiver> rtp_receiver) {}
};

class CRTCCreateSessionDescriptEventBase {
 public:
  virtual ~CRTCCreateSessionDescriptEventBase();
};

class CRTCSetSessionDescriptEventBase {
 public:
  virtual ~CRTCSetSessionDescriptEventBase();
};

class CRTCDataChannelEventBase {
 public:
  virtual ~CRTCDataChannelEventBase();
};

class CRTCDataChannel;
class CRTCPeerConnectionEvent : public CRTCPeerConnectionEventBase {
 public:
  explicit CRTCPeerConnectionEvent(const std::string& name);
  ~CRTCPeerConnectionEvent() override;

 public:
  crtc_pc_observer* Bind(
      crtc_pc_observer* observer,
      crtc::CRTCPeerConnectionEventObserver* pc_event_observer);

 protected:
  static void Event_OnSignalingChange(crtc_e_signaling_state new_state,
                                      void* context);
  static void Event_OnAddStream(HANDLE handle_ms, void* context);
  static void Event_OnRemoveStream(HANDLE handle_ms, void* context);
  static void Event_OnDataChannel(HANDLE handle_dc, void* context);
  static void Event_OnRenegotiationNeeded(void* context);
  static void Event_OnIceConnectionChange(crtc_e_ice_connection_state new_state,
                                          void* context);
  static void Event_OnStandardizedIceConnectionChange(
      crtc_e_ice_connection_state new_state,
      void* context);
  static void Event_OnConnectionChange(crtc_e_peer_connecion_state new_state,
                                       void* context);
  static void Event_OnIceGatheringChange(crtc_e_ice_gathering_state new_state,
                                         void* context);
  static void Event_OnIceCandidate(const HANDLE handle_ice_candidate,
                                   void* context);
  static void Event_OnIceCandidatesRemoved(void* context);
  static void Event_OnIceConnectionReceivingChange(bool receiving,
                                                   void* context);
  static void Event_OnAddTrack(HANDLE handle_rtp_receiver,
                               const HANDLE handle_ms_list[],
                               int size,
                               void* context);
  static void Event_OnTrack(HANDLE handle_rtp_transceiver, void* context);
  static void Event_OnRemoveTrack(HANDLE handle_rtp_reciver, void* context);
  static void Event_OnInterestingUsage(int usage_pattern, void* context);

 protected:
  crtc::CRTCPeerConnectionEventObserver* pc_event_observer_;
};

class CRTCDataChannel : public CRTCDataChannelBase {
 public:
  CRTCDataChannel();
  ~CRTCDataChannel() override;

 public:
  static bool FromHandle(HANDLE handle, CRTCDataChannel* channel);
};

class CRTCCreateSessionDescriptEvent
    : public CRTCCreateSessionDescriptEventBase {
 public:
  CRTCCreateSessionDescriptEvent();
  ~CRTCCreateSessionDescriptEvent() override;

 public:
  crtc_sdp_create_observer* Bind(crtc_sdp_create_observer* observer,
                                 void* context);

 public:
  bool Wait(int give_up_after_ms = -1);

  bool successed() const;

  const std::string& sdp() const;

 private:
  std::mutex std_mutex_;
  std::condition_variable std_cond_var;
  void* context_;
  bool processed_;
  std::string sdp_;
  bool success_;

 protected:
  static void OnEventSdpCreateOnSuccess(const char* sdp_desc,
                                        int length,
                                        void* context);
  static void OnEventSdpCreateOnFailed(int error, void* context);
};

class CRTCSetSessionDescriptEvent : public CRTCSetSessionDescriptEventBase {
 public:
  CRTCSetSessionDescriptEvent();
  ~CRTCSetSessionDescriptEvent() override;

 public:
  crtc_sdp_set_observer* Bind(crtc_sdp_set_observer* observer, void* context);

 public:
  bool Wait(int give_up_after_ms = -1);

  bool successed() const;

 private:
  std::mutex std_mutex_;
  std::condition_variable std_cond_var;
  void* context_;
  bool processed_;
  bool success_;

 protected:
  static void OnEventSdpSetOnSuccess(void* context);
  static void OnEventSdpSetOnFailed(int error, void* context);
};

class CRTCDataChannelEvent : public CRTCDataChannelEventBase {
 public:
  CRTCDataChannelEvent();
  ~CRTCDataChannelEvent() override;

 public:
  crtc_data_channel_event* Bind(crtc_data_channel_event* observer,
                                void* context);

 protected:
  // The data channel state have changed.
  static void Event_OnStateChange();
  //  A data buffer was successfully received.
  static void Event_OnMessage(const uint8_t* buffer,
                              int length,
                              bool is_binary);
  // The data channel's BufferedAmount has changed.
  static void Event_OnBufferedAmountChange(uint64_t previous_amount);

 protected:
  void* context_;
};

class CRTCStatsEvent;
class CRTCStatsEventObserver {
 public:
  virtual ~CRTCStatsEventObserver();

 public:
  virtual void OnStats(const CRTCStatsEvent* stats_event,
                       const std::string& stats_json) = 0;
};

class CRTCStatsEvent {
 public:
  CRTCStatsEvent();

 public:
  crtc_stats_observer* Bind(crtc_stats_observer* observer,
                            CRTCStatsEventObserver* event_observer_);

 protected:
  static void StatsResultCallback(const char* json, int length, void* context);

 private:
  CRTCStatsEventObserver* event_observer_;
};

class CRTCVideoFrameRender {
 public:
  enum {
    LOCAL,
    REMOTE,
  };

 public:
  CRTCVideoFrameRender(HANDLE context, int type);
  virtual ~CRTCVideoFrameRender();

 public:
  crtc_video_sink* Bind(crtc_video_sink* sink, void* context);

 protected:
  static void OnFrame(const uint8_t* y,
                      int stride_y,
                      const uint8_t* u,
                      int stride_u,
                      const uint8_t* v,
                      int stride_v,
                      int width,
                      int height,
                      HANDLE context);

 private:
  HANDLE context_;
  int type_;
};

class CRTCRTPReceiver {
 public:
  CRTCRTPReceiver() {}
  explicit CRTCRTPReceiver(HANDLE handle_rtp_receiver);
  ~CRTCRTPReceiver();

 public:
  HANDLE native_handle();

 public:
  crtc_media_type GetMediaType() const;
  CRTCMediaStreamTrack* GetMediaStreamTrack() const;

 private:
  HANDLE handle_rtp_receiver_;
  crtc_media_type media_type_;
  std::shared_ptr<CRTCMediaStreamTrack> track_;
};

class CRTCMediaStreamTrack {
 public:
  explicit CRTCMediaStreamTrack(HANDLE handle_mst);
  virtual ~CRTCMediaStreamTrack();

 protected:
  HANDLE handle_mst_;
};

class CRTCMediaStreamVideoTrack : public CRTCMediaStreamTrack {
 public:
  explicit CRTCMediaStreamVideoTrack(HANDLE handle_mst);
  ~CRTCMediaStreamVideoTrack() override;

 public:
  void AddOrUpdateSink(HANDLE handle_vsr, const crtc_video_sink_wants* wants);
  void RemoveSink(HANDLE handle_vsr);
};

class CRTCMediaStreamAudioTrack : public CRTCMediaStreamTrack {
 public:
  explicit CRTCMediaStreamAudioTrack(HANDLE handle_mst);
  ~CRTCMediaStreamAudioTrack() override;
};
}  // namespace crtc

#endif  // CRTC_CRTC_UTILS_LIBCA_CRTC_UTILS_API_H_
