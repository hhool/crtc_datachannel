/**
 * @copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-02-27
 * @file libca_media_stream.h
 * @brief media stream c api
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

/**
 * @brief destroy media stream handle
 * @param handle_ms                         handle handle_ms
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_ms_destroy(HANDLE handle_ms);

/**
 * @brief get media stream id
 * @param handle_ms                         handle handle_ms
 * @param id                                address pointer of id
 * @param length                            address pointer of length
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_ms_id(HANDLE handle_ms, char* id, int* length);

/**
 * @brief get media stream video track list
 * @param handle_ms                         handle handle_ms
 * @param handle_vts                        address pointer of handle_vts
 * @param size                              address pointer of size
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_ms_get_video_track_list(HANDLE handle_ms,
                                          HANDLE handle_vts[],
                                          int* size);

/**
 * @brief get media stream audio track list
 * @param handle_ms                         handle handle_ms
 * @param handle_ats                        handle handle_ats array address
 * pointer
 * @param size                              size address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_ms_get_audio_track_list(HANDLE handle_ms,
                                          HANDLE handle_ats[],
                                          int* size);

/**
 * @brief find video track by track id
 * @param handle_ms                         handle handle_ms
 * @param track_id                          video_track id
 * @return HANDLE                           success：!= 0，failed：== 0
 */
CRTC_API HANDLE crtc_ms_find_video_track(HANDLE handle_ms,
                                         const char* track_id);

/**
 * @brief find audio track by track id
 * @param handle_ms                         handle handle_ms
 * @param track_id                          video_track id
 * @return HANDLE                           success：!= 0，failed：== 0
 */
CRTC_API HANDLE crtc_ms_find_audio_track(HANDLE handle_ms,
                                         const char* track_id);

/**
 * @brief add video track to media stream
 * @param handle_ms                          handle handle_ms
 * @param handle_vt                          handle handle_vt
 * @return int                               success：== 0，failed：< 0
 */
CRTC_API int crtc_ms_add_video_track(HANDLE handle_ms, HANDLE handle_vt);

/**
 * @brief remove video track from media stream
 * @param handle_ms                          handle handle_ms
 * @param handle_vt                          handle handle_vt
 * @return int                               success：== 0，failed：< 0
 */
CRTC_API int crtc_ms_remove_video_track(HANDLE handle_ms, HANDLE handle_vt);

/**
 * @brief add audio track to media stream
 * @param handle_ms                          handle handle_ms
 * @param handle_at                          handle handle_vt
 * @return int                               success：== 0，failed：< 0
 */
CRTC_API int crtc_ms_add_audio_track(HANDLE handle_ms, HANDLE handle_at);

/**
 * @brief remove audio track from media stream
 * @param handle_ms                          handle handle_ms
 * @param handle_at                          handle handle_at
 * @return int                               success：== 0，failed：< 0
 */
CRTC_API int crtc_ms_remove_audio_track(HANDLE handle_ms, HANDLE handle_at);

#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_MEDIA_STREAM_H_
