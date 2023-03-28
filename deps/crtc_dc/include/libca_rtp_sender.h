/* @Copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-02-04
 * @file libca_rtp_sender.h
 * @description rtp sender c api
 */

#ifndef CRTC_CRTC_API_INCLUDE_LIBCA_RTP_SENDER_H_
#define CRTC_CRTC_API_INCLUDE_LIBCA_RTP_SENDER_H_

// clang-format off
#include "libca_common.h"
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif

/*
  rs means rtp_sender object.
*/
/** @CRTC_API int crtc_rs_set_track(HANDLE handle_rs, HANDLE handle_mst)
 * rtp_receiver 设置  media steam track 对象
 * @param handle_ms                         句柄handle_ms
 * @param handle_mst                        句柄handle_mst
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_rs_set_track(HANDLE handle_rs, HANDLE handle_mst);

/** @CRTC_API int crtc_rs_set_track(HANDLE handle_rs, HANDLE handle_mst)
 * rtp_receiver 获取  media steam track 对象
 * @param handle_ms                         句柄handle_ms
 * @param handle_mst                        句柄handle_mst结果指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_rs_get_track(HANDLE handle_rs, HANDLE* handle_mst);

/** @CRTC_API int crtc_rs_get_id(HANDLE handle_rs, char id[256])
 * rtp_receiver 获取  id
 * @param handle_ms                         句柄handle_ms
 * @param id                                id结果指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_rs_get_id(HANDLE handle_rs, char id[256]);

/** @CRTC_API int crtc_rs_get_media_type(HANDLE handle_rs, int* type);
 * rtp_receiver 获取  media type
 * @param handle_ms                         句柄handle_ms
 * @param id                                type结果指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_rs_get_media_type(HANDLE handle_rs, int* type);

/** @CRTC_API int crtc_rs_get_stream_ids(HANDLE handle_rs,
                                  char ms_ids[64][256],
                                  int* count)
 * rtp_receiver 获取  所有media stream 对象的id字符串
 * @param handle_ms                         句柄handle_ms
 * @param id                                ms_ids字符串数组结果指针
 * @count                                   media stream 个数
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_rs_get_stream_ids(HANDLE handle_rs,
                                    char ms_ids[64][256],
                                    int* count);

#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_RTP_SENDER_H_
