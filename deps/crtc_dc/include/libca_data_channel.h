/**
 * @copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-02-08
 * @file libca_data_channel.h
 * @brief data channel c api
 * @note dc means data_channel object.
 */

#ifndef CRTC_CRTC_API_INCLUDE_LIBCA_DATA_CHANNEL_H_
#define CRTC_CRTC_API_INCLUDE_LIBCA_DATA_CHANNEL_H_

// clang-format off
#include "libca_common.h"
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief C version of: https://www.w3.org/TR/webrtc/#idl-def-rtcdatachannelinit.
 * See @link crtc_pc_create_datachannel @endlink
 */
struct crtc_data_channel_init {
  /**
   * @brief Deprecated. Reliability is assumed, and channel will be unreliable
   * if maxRetransmitTime or MaxRetransmits is set.
   */
  bool reliable = false;

  /**
   * @brief True if ordered delivery is required.
   */
  bool ordered = true;

  /**
   * @brief The max period of time in milliseconds in which retransmissions will
   * be sent. After this time, no more retransmissions will be sent. -1 if
   * unset. Cannot be set along with |maxRetransmits|.
   * Negative values are ignored, and positive values are clamped to [0-65535]
   */
  int maxRetransmitTime = -1;

  /**
   * @brief The max number of retransmissions. -1 if unset.
   * Cannot be set along with |maxRetransmitTime|.
   * Negative values are ignored, and positive values are clamped to [0-65535]
   */
  int maxRetransmits = -1;

  /**
   * @brief This is set by the application and opaque to the WebRTC
   * implementation.
   */
  char protocol[256];

  /**
   * @brief True if the channel has been externally negotiated and we do not
   * send an in-band signalling in the form of an "open" message. If this is
   * true, |id| below must be set; otherwise it should be unset and will be
   * negotiated in-band.
   */
  bool negotiated = false;

  /**
   * @brief The stream id, or SID, for SCTP data channels. -1 if unset (see
   * above).
   */
  int id = -1;
};

// The data channel state have changed.
typedef void (*Event_OnStateChange)();
//  A data buffer was successfully received.
typedef void (*Event_OnMessage)(const uint8_t* buffer,
                                int length,
                                bool is_binary);
// The data channel's BufferedAmount has changed.
typedef void (*Event_OnBufferedAmountChange)(uint64_t previous_amount);

/**
 * @brief implement RTCDataChannel events.
 * See @link crtc_dc_register_observer @endlink
 * @note  code responding to these callbacks should unwind the stack before
 * using any other webrtc APIs; re-entrancy is not supported.
 */
typedef struct crtc_data_channel_event {
 public:
  /**
   * @brief notify data_channel state change. @link crtc_data_state @endlink
   */
  Event_OnStateChange OnStateChange_;
  /**
   * @brief notify data_channel received data from remote peer.
   */
  Event_OnMessage OnMessage_;
  /**
   * @brief notify data_channel buffered amount change.
   */
  Event_OnBufferedAmountChange OnBufferedAmountChange_;
} crtc_data_channel_event;

/**
 * @brief https://www.w3.org/TR/webrtc/#idl-def-rtcdatachannelstate
 * The data channel state.
 */
typedef enum crtc_data_state {
  // The DataChannel is being constructed.
  kConnecting,
  // The DataChannel is ready to send data.
  kOpen,
  // The DataChannel is in the process of closing.
  kClosing,
  // The DataChannel is closed and can no longer be used.
  kClosed
} crtc_data_state;

/**
 * @brief register data_channel event callback.
 * @param handle_dc                         HANDLE handle_dc
 * @param observer                          callback function struct pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_dc_register_observer(HANDLE handle_dc,
                                       const crtc_data_channel_event* observer);
/**
 * @brief deregister data_channel event callback.
 * @param handle_dc                         handle handle_dc
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_dc_unregister_observer(HANDLE handle_dc);

/**
 * @brief send data to data_channel.
 * @param handle_dc                         handle handle_dc
 * @param buffer                            data buffer address
 * @param length                            data length
 * @param is_binary                         binary or not
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_dc_send(HANDLE handle_dc,
                          const uint8_t* buffer,
                          int length,
                          bool is_binary);

/**
 * @brief close data_channel.
 * @param handle_dc                         handle handle_dc
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_dc_close(HANDLE handle_dc);

/**
 * @brief channel lable string.
 * @param handle_dc                         handel handle_dc
 * @param label                             label string
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_dc_lable(HANDLE handle_dc, char label[256]);

/**
 * @brief get handle_dc reliable or not.
 * @param handle_dc                         handle handle_dc
 * @param reliable                          reliable address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_dc_reliable(HANDLE handle_dc, bool* reliable);

/**
 * @brief get handle_dc ordered or not.
 * @param handle_dc                         handle handle_dc
 * @param ordered                           ordered address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_dc_ordered(HANDLE handle_dc, bool* ordered);

/**
 * @brief get data channel retransmission interval
 * @param handle_dc                         handle handle_dc
 * @param time                              time address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_dc_max_retransmit_time(HANDLE handle_dc, uint16_t* time);

/**
 * @brief get data channel retransmission max times
 * @param handle_dc                         handle handle_dc
 * @param max                               max address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_dc_max_retransmits(HANDLE handle_dc, uint16_t* max);

/**
 * @brief get data channel protocol name
 * @param handle_dc                         handle handle_dc
 * @param protocol                          protocol address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_dc_protocol(HANDLE handle_dc, char protocol[256]);

/**
 * @brief get data channel negotiated or not
 * @param handle_dc                         handle handle_dc
 * @param is_negotiated                     is_negotiated address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_dc_negotiated(HANDLE handle_dc, bool* is_negotiated);

/**
 * @brief get data channel id
 * @param handle_dc                         handle handle_dc
 * @param id                                id address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_dc_id(HANDLE handle_dc, int* id);

/**
 * @brief get data channel state
 * @param handle_dc                         handle handle_dc
 * @param state                             state address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_dc_state(HANDLE handle_dc, crtc_data_state* state);

/**
 * @brief get data channel sent messages
 * @param handle_dc                         handle handle_dc
 * @param sents                             sents address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_dc_messages_sent(HANDLE handle_dc, uint32_t* sents);

/**
 * @brief get data channel sent bytes
 * @param handle_dc                         handle handle_dc
 * @param sents                             sents address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_dc_bytes_sent(HANDLE handle_dc, uint64_t* sents);

/**
 * @brief get data channel received messages
 * @param handle_dc                         handle handle_dc
 * @param received                          received address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_dc_messages_received(HANDLE handle_dc, uint32_t* received);

/**
 * @brief get data channel received bytes
 * @param handle_dc                         handle handle_dc
 * @param received                          received address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_dc_bytes_received(HANDLE handle_dc, uint64_t* received);

/**
 * @brief get data channel buffered amount
 * @param handle_dc                         handle handle_dc
 * @param amount                            amount address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_dc_buffered_amount(HANDLE handle_dc, uint64_t* amount);

#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_DATA_CHANNEL_H_
