/**
 * @copyright (c) 2019-2023 BJY. All rights reserved.
 * @file libca_video_track.h
 * @author hhool
 * @date 2023-02-28
 * @brief video track c api
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

/**
 * @brief destroy audio_track handle handle_vt.
 * @param handle_pcf                        handle_pcf
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_vt_destroy(HANDLE handle_vt);

/**
 * @brief add or update sink of handle_vt.
 * @param handle_vt                         handle handle_vt
 * @param handle_vsr                        handle handle_vsr
 * @param video_sink_wants                  updae sink wants sturct settings
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_vt_add_or_update_sink(
    HANDLE handle_vt,
    HANDLE handle_vsr,
    const crtc_video_sink_wants* video_sink_wants);

/**
 * @brief remote sink of handle_vt.
 * @param handle_vt                         handle handle_vt
 * @param handle_vsr                        handle handle_vsr
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_vt_remove_sink(HANDLE handle_vt, HANDLE handle_vsr);

/**
 * @brief  get handle_vt id.
 * @param handle_vt                         handle handle_vt
 * @param content_hint                      hint address
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_vt_get_content_hint(HANDLE handle_vt, int* content_hint);

/**
 * @brief set handle_vt hint
 * @param handle_vt                         handle handle_vt
 * @param content_hint                      hint
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_vt_set_content_hint(HANDLE handle_vt, int content_hint);

/**
 * @brief get handle_vt handle_video_track_source handle
 * @param handle_vt                         handle handle_vt
 * @param handle_vts                        handle_vts handles array pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_vt_get_video_track_source(HANDLE handle_vt,
                                            HANDLE* handle_vts);

/**
 * @brief enable or disable video_track handle_vt
 * @param handle_vt                         handle_vt
 * @param enable                            0 disabled, !0 enable
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_vt_set_enable(HANDLE handle_vt, int enable);

/**
 * @brief get video_track handle_vt enable or disable
 * @param handle_vt                         handle_vt
 * @param enable                            func pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_vt_get_enable(HANDLE handle_vt, int* enable);
#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_VIDEO_TRACK_H_
