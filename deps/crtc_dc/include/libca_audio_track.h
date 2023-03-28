/* @Copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-02-28
 * @file libca_audio_track.h
 * @description audio track c api
 */

#ifndef CRTC_CRTC_API_INCLUDE_LIBCA_AUDIO_TRACK_H_
#define CRTC_CRTC_API_INCLUDE_LIBCA_AUDIO_TRACK_H_

// clang-format off
#include "libca_common.h"
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif

/** @CRTC_API int crtc_at_destroy(HANDLE handle_at);
 * 销毁audio_track对象句柄 handle_at.
 * @param handle_at                         handle_at
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_at_destroy(HANDLE handle_at);

/** @CRTC_API int crtc_as_destroy(HANDLE handle_as);
 * 销毁audio_source对象句柄 handle_as.
 * @param handle_as                         handle_as
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_as_destroy(HANDLE handle_as);

/** @CRTC_API int crtc_at_set_volume(HANDLE handle_as, int vol);
 * 设置audio_trak对象音量.
 * Sets the volume for the underlying MediaSource. Volume is a gain value in the
 * range 0 to 10.
 * @param handle_at                         handle_at
 * @param vol                               [0,10]
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_at_set_volume(HANDLE handle_at, double vol);

/** @CRTC_API int crtc_at_set_enable(HANDLE handle_at, int enable);
 * 设置禁用和开启audio_trak对象.
 * @param handle_at                         handle_at
 * @param enable                            0 禁用, !0 开启
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_at_set_enable(HANDLE handle_at, int enable);

/** @CRTC_API int crtc_at_get_enable(HANDLE handle_at, int enable);
 * 获取禁用和开启audio_trak对象.
 * @param handle_at                         handle_at
 * @param enable                            结果函数指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_at_get_enable(HANDLE handle_at, int* enable);
#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_AUDIO_TRACK_H_
