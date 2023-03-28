/* @Copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-02-27
 * @file libca_media_stream_track.h
 * @description media stream track c api
 */

#ifndef CRTC_CRTC_API_INCLUDE_LIBCA_MEDIA_STREAM_TRACK_H_
#define CRTC_CRTC_API_INCLUDE_LIBCA_MEDIA_STREAM_TRACK_H_

// clang-format off
#include "libca_common.h"
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif

enum crtc_e_track_state {
  kLive,
  kEnded,
};

/*
  mst means media_stream_track object.
*/
/** @CRTC_API int crtc_mst_destroy(HANDLE handle_mst);
 * 销毁 media_stream_track  对象
 * @param mst                               句柄media_stream_track
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_mst_destroy(HANDLE handle_mst);

/** @CRTC_API crtc_mst_kind(HANDLE handle_mst, char* kind, int* length);
 * 获取 media_stream_track  对象, kind 类型字符串描述
 * @param kind                              kind类型字符串描述
 * @param length                            长度结果指针地址
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_mst_kind(HANDLE handle_mst, char* kind, int* length);

/** @CRTC_API crtc_mst_id(HANDLE handle_mst, char* kind, int* length);
 * 获取 media_stream_track  对象, id 类型字符串描述
 * @param id                                id字符串描述
 * @param length                            长度结果指针地址
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_mst_id(HANDLE handle_mst, char* id, int* length);

/** @CRTC_API int crtc_mst_enabled(HANDLE handle_mst, int* enabled);
 * 获取 media_stream_track  对象, 使能状态获取
 * @param enabled                           状态结果指针地址
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_mst_enabled(HANDLE handle_mst, int* enabled);

/** @CRTC_API int crtc_mst_enabled(HANDLE handle_mst, int* enabled);
 * 设置 media_stream_track  对象, 使能状态
 * @param enable                            使能状态
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_mst_set_enabled(HANDLE handle_mst, bool enable);

/** @CRTC_API int crtc_mst_state(HANDLE handle_mst, crtc_e_track_state* state);
 * 获取 media_stream_track  对象, state状态
 * @param state                             状态结果指针地址
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_mst_state(HANDLE handle_mst, crtc_e_track_state* state);

#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_MEDIA_STREAM_TRACK_H_
