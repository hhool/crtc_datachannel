/* @Copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-02-27
 * @file libca_peer_connection_factory.h
 * @description peer connection factory c api
 */

#ifndef CRTC_CRTC_API_INCLUDE_LIBCA_PEER_CONNECTION_FACTORY_H_
#define CRTC_CRTC_API_INCLUDE_LIBCA_PEER_CONNECTION_FACTORY_H_

// clang-format off
#include "libca_common.h"
#include "libca_peer_connection.h"
#include "libca_video_codec.h"
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif

typedef enum crtc_media_type {
  MEDIA_TYPE_AUDIO,
  MEDIA_TYPE_VIDEO,
  MEDIA_TYPE_DATA
} crtc_media_type;

/*
  pcf means peer_connection_factory object.
*/

/** @CRTC_API HANDLE crtc_create_peer_connection_factory(HANDLE handle_crtc);
 * 创建peer_connection_factory对象句柄 handle_pcf, 调用crtc_pc_destroy
 * 销毁handle_pcf句柄
 * @param handle_crtc                       sdk引擎句柄
 * @param video_encoder_adapt_factory       外部视频编码器工厂(可为空)
 * @param video_decoder_adapt_factory       外部视频解码器工厂(可为空)
 * @param disable_encryption                禁用加密, 1 禁用加密, 0 启用加密
 * @param error                             创建失败返回的错误值
 * @return HANDLE                           句柄handle_pcf, 成功：非 0,失败
 */
CRTC_API HANDLE crtc_create_peer_connection_factory(
    HANDLE handle_crtc,
    crtc_video_encoder_adapt_factory* video_encoder_adapt_factory,
    crtc_video_decoder_adapt_factory* video_decoder_adapt_factory,
    int disable_encryption,
    int* error);

/** @CRTC_API HANDLE crtc_pcf_destroy(HANDLE handle_pcf);
 * 销毁peer_connection_factory对象句柄
 * @param handle_pcf                        句柄handle_pcf
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_pcf_destroy(HANDLE handle_pcf);

/** @CRTC_API HANDLE crtc_destroy_peer_connection_factory(HANDLE handle_crtc);
 * 创建peer_connection对象句柄 handle_pc. 调用crtc_pc_destroy 销毁handle_pc句柄
 * @param handle_pcf                        句柄handle_pcf
 * @param error                             创建失败返回的错误值
 * @return HANDLE                           句柄handle_pc, 成功：非 0,失败
 */
CRTC_API HANDLE
crtc_pcf_create_peer_connection(HANDLE handle_pcf,
                                const crtc_rtc_configuration* config,
                                const crtc_pc_observer* observer,
                                int* error);

/** @CRTC_API HANDLE crtc_pc_destroy(HANDLE handle_pc);
 * 销毁peer_connection对象句柄
 * @param handle_pc                         句柄handle_pcf
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_pc_destroy(HANDLE handle_pc);

/** @CRTC_API HANDLE crtc_pcf_create_local_media_stream(HANDLE handle_pcf,
                                                 const char* stream_id,
                                                 int* error);
 * 创建media_stream对象句柄 handle_ms. 调用crtc_ms_destroy 销毁handle_ms句柄
 * @param handle_pcf                        句柄handle_pcf
 * @param stream_id                         media_stream id
 * @param error                             创建失败返回的错误值
 * @return HANDLE                           句柄handle_ms, 成功：非 0,失败
 */
CRTC_API HANDLE crtc_pcf_create_local_media_stream(HANDLE handle_pcf,
                                                   const char* stream_id,
                                                   int* error);

/** @CRTC_API HANDLE crtc_pcf_create_audio_source(HANDLE handle_pcf, int*
 * error); 创建audio_source对象句柄 handle_as. 调用crtc_as_destroy
 * 销毁handle_as句柄
 * @param handle_pc                         句柄handle_pcf
 * @param error                             创建失败返回的错误值
 * @return HANDLE                           句柄handle_as, 成功：非 0,失败
 */
CRTC_API HANDLE crtc_pcf_create_audio_source(HANDLE handle_pcf, int* error);

/** @CRTC_API HANDLE crtc_pcf_create_audio_track(HANDLE handle_pcf,
                                          HANDLE handle_as,
                                          const char* label,
                                          int* error);
 * 创建audio_track对象句柄 handle_at. 调用crtc_at_destroy 销毁handle_at句柄
 * @param handle_pcf                        handle_pcf
 * @param handle_as                         handle_as
 * @param label                             audio track label
 * @param error                             创建失败返回的错误值
 * @return HANDLE                           句柄handle_vt, 成功：非 0,失败
 */
CRTC_API HANDLE crtc_pcf_create_audio_track(HANDLE handle_pcf,
                                            HANDLE handle_as,
                                            const char* label,
                                            int* error);

/** @CRTC_API HANDLE crtc_pcf_create_video_track(HANDLE handle_pcf,
                                          HANDLE handle_vs,
                                          const char* label,
                                          int* error);
 * 创建video_track对象句柄 handle_vt. 调用crtc_vt_destroy 销毁handle_vt句柄.
 * @param handle_pcf                        handle_pcf
 * @param handle_as                         handle_as
 * @param label                             video track label
 * @return HANDLE                           句柄handle_vt, 成功：非 0,失败
 */
CRTC_API HANDLE crtc_pcf_create_video_track(HANDLE handle_pcf,
                                            HANDLE handle_vs,
                                            const char* label,
                                            int* error);

#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_PEER_CONNECTION_FACTORY_H_
