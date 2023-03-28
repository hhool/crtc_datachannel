/* @Copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-02-04
 * @file libca_rtp_receiver.h
 * @description rtp receiver c api
 */

#ifndef CRTC_CRTC_API_INCLUDE_LIBCA_RTP_RECEIVER_H_
#define CRTC_CRTC_API_INCLUDE_LIBCA_RTP_RECEIVER_H_

// clang-format off
#include "libca_common.h"
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif

/*
  rr means rtp_receiver object.
*/
/** @CRTC_API int crtc_rr_get_track(HANDLE handle_rr, HANDLE* handle_mst)
 * 获取rtp_receiver 中的 media track 对象句柄数组, 以NULL结束
 * @param handle_mst                        句柄handle_mst对象结果指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_rr_get_track(HANDLE handle_rr, HANDLE* handle_mst);

/** @CRTC_API int crtc_rr_get_id(HANDLE handle_rr, char id[256]);
 * 获取rtp_receiver id
 * @param id                                结果
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_rr_get_id(HANDLE handle_rr, char id[256]);

/** @CRTC_API int crtc_rr_get_media_type(HANDLE handle_rr, int* type);
 * 获取rtp_receiver 媒体类型
 * @param type                              媒体类型结果
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_rr_get_media_type(HANDLE handle_rr, int* type);

/** @CRTC_API int crtc_rr_get_stream_ids(HANDLE handle_rr,
                                  char stream_ids[64][256],
                                  int* count)
 * 获取rtp_receiver 中 media stream track id 数组
 * Returns a list of media stream ids associated with this sender's track.
 * These are signalled in the SDP so that the remote side can associate
 * tracks.
 * @param stream_ids                        media track id 字符串数组指针的指针
 * @count                                   media track id 个数结果
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_rr_get_stream_ids(HANDLE handle_rr,
                                    char stream_ids[64][256],
                                    int* count);

/** @CRTC_API int crtc_rr_get_streams(HANDLE handle_rr,
                               HANDLE handle_ms[64],
                               int* count);
 * 获取rtp_receiver 中 media stream track 对象数组
 * @param handle_ms                         media track 对象数组指针
 * @count                                   media track id 个数结果
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_rr_get_streams(HANDLE handle_rr,
                                 HANDLE handle_ms[64],
                                 int* count);

#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_RTP_RECEIVER_H_
