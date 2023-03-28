/* @Copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2021-03-20
 * @file libca_stream_collection.h
 * @description webrtc::StreamCollectionInterface c api
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

/** @CRTC_API int crtc_sc_get_media_stream_count(HANDLE handle_sc, int32_t*
  count);
 * 获取handle_sc media stream 个数
 * @param handle_sc                         句柄handle_sc
 * @param count                             结果指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_sc_get_media_stream_count(HANDLE handle_sc, int32_t* count);

/**CRTC_API int crtc_sc_get_media_stream(HANDLE handle_sc,
                                    int32_t index,
                                    HANDLE* handle_ms)
 * 获取handle_sc 指定位置 media stream
 * @param handle_sc                         句柄handle_sc
 * @param index                             index 位置
 * @param handle_ms                         结果指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_sc_get_media_stream(HANDLE handle_sc,
                                      int32_t index,
                                      HANDLE* handle_ms);

/**CRTC_API int crtc_sc_find_media_stream(HANDLE handle_sc,
                                     const char* lable,
                                     HANDLE* handle_ms);
 * 获取handle_sc 指定lable名称 media stream
 * @param handle_sc                         句柄handle_sc
 * @param lable                             lable名称
 * @param handle_ms                         结果指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_sc_find_media_stream(HANDLE handle_sc,
                                       const char* lable,
                                       HANDLE* handle_ms);

/**CRTC_API int crtc_sc_find_media_stream(HANDLE handle_sc,
                                     const char* id,
                                     HANDLE* handle_mst);
 * 获取handle_sc 指定id名称 视频 media stream track
 * @param handle_sc                         句柄handle_sc
 * @param id                                id 名称
 * @param handle_mst                        结果指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_sc_find_video_media_stream_track(HANDLE handle_sc,
                                                   const char* id,
                                                   HANDLE* handle_mst);

/**CRTC_API int crtc_sc_find_audio_media_stream_track(HANDLE handle_sc,
                                     const char* id,
                                     HANDLE* handle_mst);
 * 获取handle_sc 指定id名称 音频 media stream track
 * @param handle_sc                         句柄handle_sc
 * @param id                                id名称
 * @param handle_mst                        结果指针
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_sc_find_audio_media_stream_track(HANDLE handle_sc,
                                                   const char* id,
                                                   HANDLE* handle_mst);

#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_STREAM_COLLECTION_H_
