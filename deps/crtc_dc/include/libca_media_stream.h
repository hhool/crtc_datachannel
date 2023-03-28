/* @Copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-02-27
 * @file libca_media_stream.h
 * @description media stream c api
 */

#ifndef CRTC_CRTC_API_INCLUDE_LIBCA_MEDIA_STREAM_H_
#define CRTC_CRTC_API_INCLUDE_LIBCA_MEDIA_STREAM_H_

// clang-format off
#include "libca_common.h"
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif

/*
ms means media stream object.
*/

/** @CRTC_API int crtc_ms_destroy(HANDLE handle_ms)
 * 销毁media stream对象句柄
 * @param handle_ms                         句柄handle_ms
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_ms_destroy(HANDLE handle_ms);

/** @CRTC_API int crtc_ms_id(HANDLE handle_ms, char* id, int* length)
 * 获取media steam id
 * @param handle_ms                         句柄handle_ms
 * @param id                                结果地址
 * @param length                            结果长度
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_ms_id(HANDLE handle_ms, char* id, int* length);

/** @CRTC_API int crtc_ms_get_video_track_list(HANDLE handle_ms,
                                        HANDLE handle_vts[],
                                        int* size)
 * 获取media steam 中含有 video track 对象数组
 * @param handle_ms                         句柄handle_ms
 * @param handle_vts                        结果地址
 * @param size                              结果长度
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_ms_get_video_track_list(HANDLE handle_ms,
                                          HANDLE handle_vts[],
                                          int* size);

/** @CRTC_API int crtc_ms_get_audio_track_list(HANDLE handle_ms,
                                        HANDLE handle_vts[],
                                        int* size)
 * 获取media steam 中含有 audio track 对象数组
 * @param handle_ms                         句柄handle_ms
 * @param handle_ats                        结果地址
 * @param size                              结果长度
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_ms_get_audio_track_list(HANDLE handle_ms,
                                          HANDLE handle_ats[],
                                          int* size);

/** @CRTC_API HANDLE crtc_ms_find_video_track(HANDLE handle_ms, const char*
  track_id)
 * 查找media steam 中 track_id 视频 video_track
 * @param handle_ms                         句柄handle_ms
 * @param track_id                          video_track id
 * @return HANDLE                           !0 成功, 0失败
 */
CRTC_API HANDLE crtc_ms_find_video_track(HANDLE handle_ms,
                                         const char* track_id);

/** @CRTC_API HANDLE crtc_ms_find_audio_track(HANDLE handle_ms, const char*
  track_id)
 * 查找media steam 中 track_id 音频 audio_track
 * @param handle_ms                         句柄handle_ms
 * @param track_id                          video_track id
 * @return HANDLE                           !0 成功, 0失败
 */
CRTC_API HANDLE crtc_ms_find_audio_track(HANDLE handle_ms,
                                         const char* track_id);

/** @CRTC_API int crtc_ms_add_video_track(HANDLE handle_ms, HANDLE handle_vt)
 * 添加 video track 到 media stream
 * @param handle_ms                         句柄handle_ms
 * @param handle_vt                         句柄handle_vt
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_ms_add_video_track(HANDLE handle_ms, HANDLE handle_vt);

/** @CRTC_API int crtc_ms_remove_video_track(HANDLE handle_ms, HANDLE handle_vt)
 * 从 media stream 移除 video track
 * @param handle_ms                         句柄handle_ms
 * @param handle_vt                         句柄handle_vt
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_ms_remove_video_track(HANDLE handle_ms, HANDLE handle_vt);

/** @CRTC_API int crtc_ms_add_audio_track(HANDLE handle_ms, HANDLE handle_at)
 * 添加 audio track 到 media stream
 * @param handle_ms                         句柄handle_ms
 * @param handle_at                         句柄handle_vt
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_ms_add_audio_track(HANDLE handle_ms, HANDLE handle_at);

/** @CRTC_API int crtc_ms_remove_audio_track(HANDLE handle_ms, HANDLE handle_at)
 * 从 media stream 移除 audio track
 * @param handle_ms                         句柄handle_ms
 * @param handle_at                         句柄handle_at
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_ms_remove_audio_track(HANDLE handle_ms, HANDLE handle_at);

#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_MEDIA_STREAM_H_
