/**
 * @copyright (c) 2019-2023 BJY. All rights reserved.
 * @brief audio track c api
 * @file libca_audio_track.h
 * @author hhool
 * @date 2023-02-28
 */
#ifndef CRTC_CRTC_API_INCLUDE_LIBCA_AUDIO_TRACK_H_
#define CRTC_CRTC_API_INCLUDE_LIBCA_AUDIO_TRACK_H_

// clang-format off
#include "libca_common.h"
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief destroy audio_track handle handle_at.
 * @param handle_at                         handle_at audio_track handle
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_at_destroy(HANDLE handle_at);

/**
 * @brief destroy audio_source handle handle_as.
 * @param handle_as                         handle_as audio_source handle
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_as_destroy(HANDLE handle_as);

/**
 * @brief set audio_track vol.
 * Sets the volume for the underlying MediaSource. Volume is a gain value in the
 * range 0 to 10.
 * @param handle_at                         handle_at audio_track handle
 * @param vol                               [0,10]
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_at_set_volume(HANDLE handle_at, double vol);

/**
 * @brief set disable or enable audio_trak对象.
 * @param handle_at                         handle_at audio_track handle
 * @param enable                            0 disabled, !0 enable
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_at_set_enable(HANDLE handle_at, int enable);

/**
 * @brief get disable or enable audio_trak对象.
 * @param handle_at                         handle_at audio_track handle
 * @param enable                            func pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_at_get_enable(HANDLE handle_at, int* enable);
#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_AUDIO_TRACK_H_
