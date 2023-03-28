/* @Copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-02-28
 * @file libca_video_track.h
 * @description video track c api
 */

#ifndef CRTC_CRTC_API_INCLUDE_LIBCA_VIDEO_TRACK_H_
#define CRTC_CRTC_API_INCLUDE_LIBCA_VIDEO_TRACK_H_

// clang-format off
#include "libca_common.h"
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif

enum ContentHint {
  kContentHint_None,
  kContentHint_Fluid,
  kContentHint_Detailed,
  kContentHint_Text
};
/*
vt means video_track object.
vsr means video sink render object.
*/

/** @CRTC_API int crtc_vt_destroy(HANDLE handle_vt);
 * 销毁audio_track对象句柄 handle_vt.
 * @param handle_pcf                        handle_pcf
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_vt_destroy(HANDLE handle_vt);

/** @CRTC_API int crtc_vt_add_or_update_sink(
    HANDLE handle_vt,
    HANDLE handle_vsr,
    const crtc_video_sink_wants* video_sink_wants);
 * 连接handle_vsr
 * @param handle_vt                         句柄handle_vt
 * @param handle_vsr                        句柄handle_vsr
 * @param video_sink_wants                  连接设置
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_vt_add_or_update_sink(
    HANDLE handle_vt,
    HANDLE handle_vsr,
    const crtc_video_sink_wants* video_sink_wants);

/** @CRTC_API int crtc_vt_remove_sink(
    HANDLE handle_vt,
    HANDLE handle_vsr);
 * 反连接handle_vsr
 * @param handle_vt                         句柄handle_vt
 * @param handle_vsr                        句柄handle_vsr
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_vt_remove_sink(HANDLE handle_vt, HANDLE handle_vsr);

/** @CRTC_API int crtc_vt_get_content_hint(HANDLE handle_vt, int* content_hint);
 * 获取handle_vt hint 设置
 * @param handle_vt                         句柄handle_vt
 * @param content_hint                      hint结果地址指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_vt_get_content_hint(HANDLE handle_vt, int* content_hint);

/** @CRTC_API int crtc_vt_set_content_hint(HANDLE handle_vt, int* content_hint);
 * 设置handle_vt hint
 * @param handle_vt                         句柄handle_vt
 * @param content_hint                      hint
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_vt_set_content_hint(HANDLE handle_vt, int content_hint);

/** @CRTC_API int crtc_vt_get_video_track_source(HANDLE handle_vt,
                                          HANDLE* handle_vts);
 * 获取handle_vt handle_video_track_source对象
 * @param handle_vt                         句柄handle_vt
 * @param handle_vts                        handle_vts 对象结果地址指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_vt_get_video_track_source(HANDLE handle_vt,
                                            HANDLE* handle_vts);

/** @CRTC_API int crtc_vt_set_enable(HANDLE handle_vt, int enable);
 * 设置禁用和开启video_trak对象.
 * @param handle_vt                         handle_vt
 * @param enable                            0 禁用, !0 开启
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_vt_set_enable(HANDLE handle_vt, int enable);

/** @CRTC_API int crtc_vt_get_enable(HANDLE handle_vt, int enable);
 * 获取禁用和开启video_trak对象.
 * @param handle_vt                         handle_vt
 * @param enable                            结果函数指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_vt_get_enable(HANDLE handle_vt, int* enable);
#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_VIDEO_TRACK_H_
