/**
 * @copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-02-27
 * @file libca_media_stream_track.h
 * @brief media stream track c api
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
/**
 * @brief destroy media stream track handle
 * @param mst                                handle media_stream_track
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_mst_destroy(HANDLE handle_mst);

/**
 * @brief get media stream track kind
 * @param kind                              kind string address.
 * @param length                            address of length
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_mst_kind(HANDLE handle_mst, char* kind, int* length);

/**
 * @brief get media stream track id
 * @param id                                id string address.
 * @param length                            address of length
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_mst_id(HANDLE handle_mst, char* id, int* length);

/**
 * @brief get media stream track enabled
 * @param enabled                           address of enabled
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_mst_enabled(HANDLE handle_mst, int* enabled);

/**
 * @brief set media stream track enabled
 * @param enable                            enable or not
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_mst_set_enabled(HANDLE handle_mst, bool enable);

/**
 * @brief get media stream track state
 * @param state                             address of state
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_mst_state(HANDLE handle_mst, crtc_e_track_state* state);

#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_MEDIA_STREAM_TRACK_H_
