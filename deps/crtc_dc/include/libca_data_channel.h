/* @Copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-02-08
 * @file libca_data_channel.h
 * @description data channel c api
 */

#ifndef CRTC_CRTC_API_INCLUDE_LIBCA_DATA_CHANNEL_H_
#define CRTC_CRTC_API_INCLUDE_LIBCA_DATA_CHANNEL_H_

// clang-format off
#include "libca_common.h"
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif

struct crtc_data_channel_init {
  // Deprecated. Reliability is assumed, and channel will be unreliable if
  // maxRetransmitTime or MaxRetransmits is set.
  bool reliable = false;

  // True if ordered delivery is required.
  bool ordered = true;

  // The max period of time in milliseconds in which retransmissions will be
  // sent. After this time, no more retransmissions will be sent. -1 if unset.
  //
  // Cannot be set along with |maxRetransmits|.
  int maxRetransmitTime = -1;

  // The max number of retransmissions. -1 if unset.
  //
  // Cannot be set along with |maxRetransmitTime|.
  int maxRetransmits = -1;

  // This is set by the application and opaque to the WebRTC implementation.
  char protocol[256];

  // True if the channel has been externally negotiated and we do not send an
  // in-band signalling in the form of an "open" message. If this is true, |id|
  // below must be set; otherwise it should be unset and will be negotiated
  // in-band.
  bool negotiated = false;

  // The stream id, or SID, for SCTP data channels. -1 if unset (see above).
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

// Used to implement RTCDataChannel events.
// The code responding to these callbacks should unwind the stack before
// using any other webrtc APIs; re-entrancy is not supported.
typedef struct crtc_data_channel_event {
 public:
  // The data channel state have changed.
  Event_OnStateChange OnStateChange_;
  //  A data buffer was successfully received.
  Event_OnMessage OnMessage_;
  // The data channel's BufferedAmount has changed.
  Event_OnBufferedAmountChange OnBufferedAmountChange_;
} crtc_data_channel_event;

typedef enum crtc_data_state {
  kConnecting,
  kOpen,  // The DataChannel is ready to send data.
  kClosing,
  kClosed
} crtc_data_state;

/*
dc means data_channel object.
*/
/** @CRTC_API int crtc_dc_register_observer(HANDLE handle_dc,
                                     const crtc_data_channel_event* observer)
 * 注册data_channel 事件回调
 * @param handle_dc                         句柄handle_dc
 * @param observer                          回调函数结构体
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_dc_register_observer(HANDLE handle_dc,
                                       const crtc_data_channel_event* observer);
/** @CRTC_API int crtc_dc_unregister_observer(HANDLE handle_dc)
 * 反注册data_channel 事件回调
 * @param handle_dc                         句柄handle_dc
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_dc_unregister_observer(HANDLE handle_dc);

/** @CRTC_API int crtc_dc_send(HANDLE handle_dc,
                        const uint8_t* buffer,
                        int length,
                        bool is_binary)
 * 发送数据
 * @param handle_dc                         句柄handle_dc
 * @param buffer                            数据内容
 * @param length                            数据长度
 * @param is_binary                         是否二进制
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_dc_send(HANDLE handle_dc,
                          const uint8_t* buffer,
                          int length,
                          bool is_binary);

/** @CRTC_API int crtc_dc_close(HANDLE handle_dc)
 * 关闭handle_dc通道句柄
 * @param handle_dc                         句柄handle_dc
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_dc_close(HANDLE handle_dc);

/** @CRTC_API int crtc_dc_lable(HANDLE handle_dc, char label[256])
 * 获取data channel lable名称字符串
 * @param handle_dc                         句柄handle_dc
 * @param label                             label字符串地址
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_dc_lable(HANDLE handle_dc, char label[256]);

/** @CRTC_API int crtc_dc_reliable(HANDLE handle_dc, bool* reliable)
 * 获取data channel 是否可靠传输
 * @param handle_dc                         句柄handle_dc
 * @param reliable                          结果地址指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_dc_reliable(HANDLE handle_dc, bool* reliable);

/** @CRTC_API int crtc_dc_ordered(HANDLE handle_dc, bool* ordered)
 * 获取data channel 是否有序传输
 * @param handle_dc                         句柄handle_dc
 * @param ordered                           结果地址指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_dc_ordered(HANDLE handle_dc, bool* ordered);

/** @CRTC_API int crtc_dc_max_retransmit_time(HANDLE handle_dc, uint16_t* time)
 * 获取data channel 重传事件间隔
 * @param handle_dc                         句柄handle_dc
 * @param time                              结果地址指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_dc_max_retransmit_time(HANDLE handle_dc, uint16_t* time);

/** @CRTC_API int crtc_dc_max_retransmit_time(HANDLE handle_dc, uint16_t* max)
 * 获取data channel 重传最大尝试次数
 * @param handle_dc                         句柄handle_dc
 * @param max                               结果地址指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_dc_max_retransmits(HANDLE handle_dc, uint16_t* max);

/** @CRTC_API int crtc_dc_protocol(HANDLE handle_dc, char protocol[256]);
 * 获取data channel 传输协议名称
 * @param handle_dc                         句柄handle_dc
 * @param protocol                          结果地址指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_dc_protocol(HANDLE handle_dc, char protocol[256]);

/** @CRTC_API int crtc_dc_protocol(HANDLE handle_dc, char protocol[256]);
 * 获取data channel 是否协商
 * @param handle_dc                         句柄handle_dc
 * @param is_negotiated                     结果地址指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_dc_negotiated(HANDLE handle_dc, bool* is_negotiated);

/** @CRTC_API int crtc_dc_id(HANDLE handle_dc, int* id);
 * 获取data channel 通道id
 * @param handle_dc                         句柄handle_dc
 * @param id                                结果地址指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_dc_id(HANDLE handle_dc, int* id);

/** @CRTC_API int crtc_dc_state(HANDLE handle_dc, crtc_data_state* state);
 * 获取data channel 通道状态
 * @param handle_dc                         句柄handle_dc
 * @param state                             结果地址指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_dc_state(HANDLE handle_dc, crtc_data_state* state);

/** @CRTC_API int crtc_dc_messages_sent(HANDLE handle_dc, uint32_t* sents);
 * 获取data channel 已发送消息条目数
 * @param handle_dc                         句柄handle_dc
 * @param sents                             结果地址指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_dc_messages_sent(HANDLE handle_dc, uint32_t* sents);

/** @CRTC_API int crtc_dc_bytes_sent(HANDLE handle_dc, uint64_t* sents);
 * 获取data channel 已发送字节总数目
 * @param handle_dc                         句柄handle_dc
 * @param sents                             结果地址指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_dc_bytes_sent(HANDLE handle_dc, uint64_t* sents);

/** @CRTC_API int crtc_dc_messages_received(HANDLE handle_dc, uint32_t*
 * received); 获取data channel 已接收消息条目数
 * @param handle_dc                         句柄handle_dc
 * @param received                          结果地址指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_dc_messages_received(HANDLE handle_dc, uint32_t* received);

/** @CRTC_API int crtc_dc_bytes_received(HANDLE handle_dc, uint64_t* received);
 * 获取data channel 已接收字节总目数
 * @param handle_dc                         句柄handle_dc
 * @param received                          结果地址指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_dc_bytes_received(HANDLE handle_dc, uint64_t* received);

/** @CRTC_API int crtc_dc_buffered_amount(HANDLE handle_dc, uint64_t* amount);
 * 获取data channel 当前发送剩余未发送的字节数
 * @param handle_dc                         句柄handle_dc
 * @param amount                            结果地址指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_dc_buffered_amount(HANDLE handle_dc, uint64_t* amount);

#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_DATA_CHANNEL_H_
