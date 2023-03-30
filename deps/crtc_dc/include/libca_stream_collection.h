/**
 * @copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2021-03-20
 * @file libca_stream_collection.h
 * @brief webrtc::StreamCollectionInterface c api
 */

#ifndef CRTC_CRTC_API_INCLUDE_LIBCA_STREAM_COLLECTION_H_
#define CRTC_CRTC_API_INCLUDE_LIBCA_STREAM_COLLECTION_H_

// clang-format off
#include "libca_common.h"
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif

/*
  sc means stream_collection object.
*/

/**
 * @brief get media stream count.
 * @param handle_sc                         handle handle_sc
 * @param count                             count address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_sc_get_media_stream_count(HANDLE handle_sc, int32_t* count);

/**
 * @brief get media stream(handle_ms) by index.
 * @param handle_sc                         handle handle_sc
 * @param index                             index pos
 * @param handle_ms                         handle_ms address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_sc_get_media_stream(HANDLE handle_sc,
                                      int32_t index,
                                      HANDLE* handle_ms);

/**
 * @brief find media stream(handle_ms) by lable.
 * @param handle_sc                         handle handle_sc
 * @param lable                             lable address pointer
 * @param handle_ms                         handle_ms address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_sc_find_media_stream(HANDLE handle_sc,
                                       const char* lable,
                                       HANDLE* handle_ms);

/**
 * @brief find video media stream track(handle_mst) by id.
 * @param handle_sc                         handle handle_sc
 * @param id                                id address pointer
 * @param handle_mst                        handle_mst address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_sc_find_video_media_stream_track(HANDLE handle_sc,
                                                   const char* id,
                                                   HANDLE* handle_mst);

/**
 * @brief get audio media stream track(handle_mst) by id.
 * @param handle_sc                         handle handle_sc
 * @param id                                id address pointer
 * @param handle_mst                        handle_mst address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_sc_find_audio_media_stream_track(HANDLE handle_sc,
                                                   const char* id,
                                                   HANDLE* handle_mst);

#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_STREAM_COLLECTION_H_
