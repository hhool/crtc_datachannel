/**
 * @copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-02-27
 * @file libca_peer_connection.h
 * @brief peer connection c api
 */

#ifndef CRTC_CRTC_API_INCLUDE_LIBCA_PEER_CONNECTION_H_
#define CRTC_CRTC_API_INCLUDE_LIBCA_PEER_CONNECTION_H_

// clang-format off
#include "libca_common.h"
#include "libca_data_channel.h"
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif

enum crtc_sdp_semantics { kPlanB, kUnifiedPlan };
// See https://w3c.github.io/webrtc-pc/#rtcsignalingstate-enum
enum crtc_e_signaling_state {
  kSignalState_Stable,
  kSignalState_HaveLocalOffer,
  kSignalState_HaveLocalPrAnswer,
  kSignalState_HaveRemoteOffer,
  kSignalState_HaveRemotePrAnswer,
  kSignalState_Closed,
};

// See https://w3c.github.io/webrtc-pc/#dom-rtcicegatheringstate
enum crtc_e_ice_gathering_state {
  kIceGatheringNew,
  kIceGatheringGathering,
  kIceGatheringComplete
};

// See https://w3c.github.io/webrtc-pc/#dom-rtcpeerconnectionstate
enum crtc_e_peer_connecion_state {
  kPeerConnectionState_New,
  kPeerConnectionState_Connecting,
  kPeerConnectionState_Connected,
  kPeerConnectionState_Disconnected,
  kPeerConnectionState_Failed,
  kPeerConnectionState_Closed,
};

// See https://w3c.github.io/webrtc-pc/#dom-rtciceconnectionstate
enum crtc_e_ice_connection_state {
  kIceConnectionNew,
  kIceConnectionChecking,
  kIceConnectionConnected,
  kIceConnectionCompleted,
  kIceConnectionFailed,
  kIceConnectionDisconnected,
  kIceConnectionClosed,
  kIceConnectionMax,
};

// TLS certificate policy.
enum crtc_e_tls_cert_policy {
  kTlsCertPolicySecure,
  kTlsCertPolicyInsecureNoCheck,
};

enum crtc_e_ice_transports_type { kIceNone, kRelay, kNoHost, kAll };

enum crtc_e_bundle_policy {
  kBundlePolicyBalanced,
  kBundlePolicyMaxBundle,
  kBundlePolicyMaxCompat
};

enum crtc_e_rtcp_mux_policy {
  kRtcpMuxPolicyNegotiate,
  kRtcpMuxPolicyRequire,
};

enum crtc_e_tcp_candidate_policy {
  kTcpCandidatePolicyEnabled,
  kTcpCandidatePolicyDisabled
};

enum crtc_e_candidate_network_policy {
  kCandidateNetworkPolicyAll,
  kCandidateNetworkPolicyLowCost
};

enum crtc_e_continunal_gathering_policy { GATHER_ONCE, GATHER_CONTINUALLY };

enum crtc_e_rtc_configuration_type { kSafe, kAggressive };

typedef void (*crtc_rtc_video_encoded_frame_cb_func)(const char* stream_ssrc,
                                                     const uint8_t* frame,
                                                     uint32_t frame_size,
                                                     uint32_t frame_width,
                                                     uint32_t frame_height,
                                                     uint32_t timestamp);
typedef struct crtc_rtc_configuration {
  // defualt kUnifiedPlan
  crtc_sdp_semantics sdp_semantics_;
  // defualt kAll
  crtc_e_ice_transports_type type_;
  // defualt kBundlePolicyBalanced;
  crtc_e_bundle_policy bundle_policy_;
  // defualt kRtcpMuxPolicyRequire;
  crtc_e_rtcp_mux_policy rtcp_mux_policy_;
  // defualt kTcpCandidatePolicyEnabled;
  crtc_e_tcp_candidate_policy tcp_candidate_policy_;
  // defualt 1
  int enable_dtls_srtp_;
  //
  char turn_uri_[1024];
  // defualt 0
  int min_port_;
  // defualt 0
  int port_range_length_;
  // output video encoded stream
  crtc_rtc_video_encoded_frame_cb_func video_encoded_frame_callback;
} crtc_rtc_configuration;

/*static const int kUndefined = -1;
static const int kMaxOfferToReceiveMedia = 1;
static const int kOfferToReceiveMediaTrue = 1;
*/

typedef struct crtc_rtc_offer_answer_options {
  int offer_to_receive_video = -1;
  int offer_to_receive_audio = -1;
  int num_simulcast_layers = 1;
  bool voice_activity_detection = true;
  bool ice_restart = false;
  bool use_rtp_mux = true;
} crtc_rtc_offer_answer_options;

enum crtc_e_stats_output_level {
  kStatsOutputLevelStandard,
  kStatsOutputLevelDebug,
};

// Enumeration to represent distinct classes of errors that an application
// may wish to act upon differently. These roughly map to DOMExceptions or
// RTCError "errorDetailEnum" values in the web API, as described in the
// comments below.
enum crtc_e_error {
  // No error.
  NONE,

  // An operation is valid, but currently unsupported.
  // Maps to OperationError DOMException.
  UNSUPPORTED_OPERATION,

  // A supplied parameter is valid, but currently unsupported.
  // Maps to OperationError DOMException.
  UNSUPPORTED_PARAMETER,

  // General error indicating that a supplied parameter is invalid.
  // Maps to InvalidAccessError or TypeError DOMException depending on context.
  INVALID_PARAMETER,

  // Slightly more specific than INVALID_PARAMETER; a parameter's value was
  // outside the allowed range.
  // Maps to RangeError DOMException.
  INVALID_RANGE,

  // Slightly more specific than INVALID_PARAMETER; an error occurred while
  // parsing string input.
  // Maps to SyntaxError DOMException.
  SYNTAX_ERROR,

  // The object does not support this operation in its current state.
  // Maps to InvalidStateError DOMException.
  INVALID_STATE,

  // An attempt was made to modify the object in an invalid way.
  // Maps to InvalidModificationError DOMException.
  INVALID_MODIFICATION,

  // An error occurred within an underlying network protocol.
  // Maps to NetworkError DOMException.
  NETWORK_ERROR,

  // Some resource has been exhausted; file handles, hardware resources, ports,
  // etc.
  // Maps to OperationError DOMException.
  RESOURCE_EXHAUSTED,

  // The operation failed due to an internal error.
  // Maps to OperationError DOMException.
  INTERNAL_ERROR,
};

typedef void (*Event_OnSignalingChange)(crtc_e_signaling_state new_state,
                                        void* context);
typedef void (*Event_OnAddStream)(HANDLE handle_ms, void* context);
typedef void (*Event_OnRemoveStream)(HANDLE handle_ms, void* context);
typedef void (*Event_OnDataChannel)(HANDLE handle_dc, void* context);
typedef void (*Event_OnRenegotiationNeeded)(void* context);
typedef void (*Event_OnIceConnectionChange)(
    crtc_e_ice_connection_state new_state,
    void* context);
typedef void (*Event_OnStandardizedIceConnectionChange)(
    crtc_e_ice_connection_state new_state,
    void* context);
typedef void (*Event_OnConnectionChange)(crtc_e_peer_connecion_state new_state,
                                         void* context);
typedef void (*Event_OnIceGatheringChange)(crtc_e_ice_gathering_state new_state,
                                           void* context);
typedef void (*Event_OnIceCandidate)(const HANDLE handle_ice_candidate,
                                     void* context);
typedef void (*Event_OnIceCandidatesRemoved)(void* context);
typedef void (*Event_OnIceConnectionReceivingChange)(bool receiving,
                                                     void* context);
typedef void (*Event_OnAddTrack)(HANDLE handle_rtp_receiver,
                                 const HANDLE handle_ms_list[],
                                 int size,
                                 void* context);
typedef void (*Event_OnTrack)(HANDLE handle_rtp_transceiver, void* context);
typedef void (*Event_OnRemoveTrack)(HANDLE handle_rtp_receiver, void* context);
typedef void (*Event_OnInterestingUsage)(int usage_pattern, void* context);

typedef struct crtc_pc_observer {
  Event_OnSignalingChange OnSignalingChange_;
  Event_OnAddStream OnAddStream_;
  Event_OnRemoveStream OnRemoveStream_;
  Event_OnDataChannel OnDataChannel_;
  Event_OnRenegotiationNeeded OnRenegotiationNeeded_;
  Event_OnIceConnectionChange OnIceConnectionChange_;
  Event_OnStandardizedIceConnectionChange OnStandardizedIceConnectionChange_;
  Event_OnConnectionChange OnConnectionChange_;
  Event_OnIceGatheringChange OnIceGatheringChange_;
  Event_OnIceCandidate OnIceCandidate_;
  Event_OnIceCandidatesRemoved OnIceCandidatesRemoved_;
  Event_OnIceConnectionReceivingChange OnIceConnectionReceivingChange_;
  Event_OnAddTrack OnAddTrack_;
  Event_OnTrack OnTrack_;
  Event_OnRemoveTrack OnRemoveTrack_;
  Event_OnInterestingUsage OnInterestingUsage_;
  void* context_;
} crtc_pc_observer;

typedef void (*Event_Sdp_Create_OnSuccess)(const char* sdp_desc,
                                           int length,
                                           void* context);
typedef void (*Event_Sdp_Create_OnFailed)(int error, void* context);
typedef struct crtc_sdp_create_observer {
  void* Context_;
  Event_Sdp_Create_OnSuccess OnSuccess_;
  Event_Sdp_Create_OnFailed OnFailed_;
} crtc_sdp_create_observer;

typedef void (*Event_Sdp_Set_OnSuccess)(void* context);
typedef void (*Event_Sdp_Set_OnFailed)(int error, void* context);
typedef struct crtc_sdp_set_observer {
  void* Context_;
  Event_Sdp_Set_OnSuccess OnSuccess_;
  Event_Sdp_Set_OnFailed OnFailed_;
} crtc_sdp_set_observer;

typedef void (*Event_Stats_Callback)(const char* json,
                                     int length,
                                     void* context);
typedef struct crtc_stats_observer {
  void* Context_;
  Event_Stats_Callback Callback_;
} crtc_stats_observer;
/*
  pc means peer_connection object.
*/
/**
 * @brief Accessor methods to active local streams.
 * This method is not supported with kUnifiedPlan semantics. Please use
 * GetSenders() instead.
 * @param handle_ms                         handle handle_pc
 * @param handle_sc                         pointer to the result
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pc_get_local_stream(HANDLE handle_pc, HANDLE* handle_sc);

/**
 * @brief Accessor methods to active local streams.
 * This method is not supported with kUnifiedPlan semantics. Please use
 * GetSenders() instead.
 * @param handle_ms                         handle handle_pc
 * @param handle_sc                         pointer to the result
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pc_get_remote_stream(HANDLE handle_pc, HANDLE* handle_sc);

/**
 * @brief This method is not supported with kUnifiedPlan semantics. Please use
 * AddTrack instead.
 * @param handle_pc                         handle handle_pc
 * @param handle_ms                         handle handle_ms
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pc_add_stream(HANDLE handle_pc, HANDLE handle_ms);

/**
 * @brief This method is not supported with kUnifiedPlan semantics. Please use
 * AddTrack instead.
 * @param handle_pc                         handle handle_pc
 * @param handle_ms                         handle handle_ms
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pc_remove_stream(HANDLE handle_pc, HANDLE handle_ms);

/**
 * @brief This method is not supported with kUnifiedPlan semantics. Please use
 * AddTrack instead.
 * @param handle_pc                         handle handle_pc
 * @param handle_mst                        handle handle_mst
 * @param error                             error code pointer address
 * @return HANDLE                           success：!0，failed：0 handle_rs
 */
CRTC_API HANDLE crtc_pc_add_track(HANDLE handle_pc,
                                  HANDLE handle_mst,
                                  int* error);

/**
 * @brief This method is not supported with kUnifiedPlan semantics. Please use
 * AddTrack instead.
 * @param handle_pc                         handle handle_pc
 * @param handle_rs                         handle handle_rs
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pc_remove_track(HANDLE handle_pc, HANDLE handle_rs);

/**
 * @brief Create a new offer
 * @param handle_pc                         handle handle_pc
 * @param crtc_sdp_create_observer          callback function to handle the result
 * @param options                           options to create offer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pc_create_offer(HANDLE handle_pc,
                                  const crtc_sdp_create_observer* observer,
                                  const crtc_rtc_offer_answer_options* options);

/**
 * @brief Create an answer to an offer
 * @param handle_pc                         handle handle_pc
 * @param crtc_sdp_create_observer          callback function to handle the result
 * @param options                           options to create answer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pc_create_answer(
    HANDLE handle_pc,
    const crtc_sdp_create_observer* observer,
    const crtc_rtc_offer_answer_options* options);

/**
 * @brief Sets the local session description.
 * @param handle_pc                         handle handle_pc
 * @param observer                          callback function to handle the result
 * @param sdp_type                          sdp type
 * @param session_description               sdp candidate
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pc_set_local_description(
    HANDLE handle_pc,
    const crtc_sdp_set_observer* observer,
    int sdp_type,
    const char* session_description);

/**
 * @brief Sets the remote session description.
 * @param handle_pc                         handle handle_pc
 * @param observer                          callback function to handle the result
 * @param sdp_type                          sdp type
 * @param session_description               sdp candidate
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pc_set_remote_description(
    HANDLE handle_pc,
    const crtc_sdp_set_observer* observer,
    int sdp_type,
    const char* session_description);

/**
 * @brief Provides a remote candidate to the ICE Agent.
 * @param handle_pc                         handle handle_pc
 * @param sdp_mid                           this is the value of the "a=mid"
                                            attribute of the candidate's
                                            m= section in SDP, which identifies
                                            the m= section.
 * @param sdp_mline_index                   This indicates the index (starting
                                            at zero) of m= section this
                                            candidate is associated with.
                                            Needed when an endpoint doesn't
                                            support MIDs.
 * @param ice_candidate_sdp                 sdp candidate
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pc_add_ice_candidate(HANDLE handle_pc,
                                       const char* sdp_mid,
                                       int sdp_mline_index,
                                       const char* ice_candidate_sdp);

/**
 * @brief remove the remote session description.
 * @param handle_pc                         handle handle_pc
 * @param ice_candidate_sdp                 sdp candidate
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pc_remove_ice_candidate(HANDLE handle_pc,
                                          const char* ice_candidate_sdp);

/**
 * @brief This method is not supported with kUnifiedPlan semantics. Please use
 * AddTrack instead.
 * @param handle_pc                         handle handle_pc
 * @param state                             state crtc_e_signaling_state
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pc_signaling_state(HANDLE handle_pc,
                                     crtc_e_signaling_state* state);

/**
 * @brief This method is not supported with kUnifiedPlan semantics. Please use
 * AddTrack instead.
 * @param handle_pc                         handle handle_pc
 * @param state                             state crtc_e_ice_connection_state
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pc_ice_connection_state(HANDLE handle_pc,
                                          crtc_e_ice_connection_state* state);

/**
 * @brief get pc ice connection state. This method is not supported with
 *  kUnifiedPlan semantics. Please use AddTrack instead.
 * @param handle_pc                         handle handle_pc
 * @param state                             state crtc_e_peer_connecion_state
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pc_peer_connection_state(HANDLE handle_pc,
                                           crtc_e_peer_connecion_state* state);

/**
 * @brief get ice gathering state.
 * @param handle_pc                         handle handle_pc
 * @param state                             state crtc_e_ice_gathering_state
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pc_ice_gathering_state(HANDLE handle_pc,
                                         crtc_e_ice_gathering_state* state);

/**
 * @brief get senders.
 * @param handle_pc                         handle handle_pc
 * @param handle_rs                         handle_rs array
 * @param size                              address pointer of size
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pc_get_senders(HANDLE handle_pc,
                                 HANDLE handle_rs[64],
                                 int* size);

/**
 * @brief get receivers.
 * @param handle_pc                         handle handle_pc
 * @param handle_rr                         handle_rr array
 * @param size                              address pointer of size
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pc_get_receivers(HANDLE handle_pc,
                                   HANDLE handle_rr[64],
                                   int* size);

/**
 * @brief get stats.
 * @param handle_pc                         handle handle_pc
 * @param observer                          callback function of stats
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pc_get_stats(HANDLE handle_pc,
                               const crtc_stats_observer* observer);

/**
 * @brief get sender stats.
 * @param handle_pc                         handle handle_pc
 * @param handl_rs                          handle handl_rs
 * @param observer                          callback function of stats
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pc_get_sender_stats(HANDLE handle_pc,
                                      HANDLE handle_rs,
                                      const crtc_stats_observer* observer);

/**
 * @brief get receiver stats.
 * @param handle_pc                         handle handle_pc
 * @param handl_rr                          handle handl_rr
 * @param observer                          callback function of stats
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pc_get_receiver_stats(HANDLE handle_pc,
                                        HANDLE handle_rtp_receiver,
                                        const crtc_stats_observer* observer);

/**
 * @brief get media stream track stats.
 * @param handle_pc                         handle handle_pc
 * @param handl_mst                         handle handl_mst
 * @param level                             stats level
 * @param observer                          callback function of stats
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pc_get_media_stream_track_stats(
    HANDLE handle_pc,
    const HANDLE handl_mst,
    int level,
    const crtc_stats_observer* observer);

/**
 * @brief create datachannel.
 * @param handle_pc                         handle handle_pc
 * @param label                             label of datachannel
 * @param dc_init                           dc init of datachannel
 * @return int                              success： !0，failed： 0
 */
CRTC_API HANDLE
crtc_pc_create_datachannel(HANDLE handle_pc,
                           const char label[256],
                           const crtc_data_channel_init* dc_init);

/**
 * @brief close peer connection.
 * @param handle_pc                         handle handle_pc
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pc_close(HANDLE handle_pc);

/**
 * @brief set encoding parameters by track.
 * @param handle_pc                         peer_connectionhandle
 * @param handle_track                      track handle
 * @param max_framerate                     max framerate
 * @param label                             label of datachannel
 * @param dc_init                           min bitrate
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_rtc_set_encoding_parameters_by_track(HANDLE handle_pc,
                                                       HANDLE handle_track,
                                                       int max_framerate,
                                                       int max_bitrate_bps,
                                                       int min_bitrate_bps);

#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_PEER_CONNECTION_H_
