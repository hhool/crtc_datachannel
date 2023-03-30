/**
 * @copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-02-27
 * @file libca_peer_connection_factory.h
 * @brief peer connection factory c api
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

/**
 * @brief create peer_connection_factory handle_pcf, call crtc_pcf_destroy
 * destroy handle_pcf
 * @param handle_crtc                       handle of crtc
 * @param video_encoder_adapt_factory       external video encoder factory (can
 * be null)
 * @param video_decoder_adapt_factory       external video decoder factory (can
 * be null)
 * @param disable_encryption                enable/disable encryption
 * @param error                             error code if failed
 * @return HANDLE                           handle of peer_connection_factory,
 * success: non 0, failed: 0
 */
CRTC_API HANDLE crtc_create_peer_connection_factory(
    HANDLE handle_crtc,
    crtc_video_encoder_adapt_factory* video_encoder_adapt_factory,
    crtc_video_decoder_adapt_factory* video_decoder_adapt_factory,
    int disable_encryption,
    int* error);

/**
 * @brief destroy peer_connection_factory handle_pcf
 * @param handle_pcf                        handle handle_pcf
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pcf_destroy(HANDLE handle_pcf);

/**
 * @brief create peer_connection handle handle_pc. call crtc_pc_destroy destroy
 * handle_pc
 * @param handle_pcf                        handle handle_pcf
 * @param config                            peer_connection config
 * @param observer                          peer_connection observer
 * @param error                             error code if failed
 * @return HANDLE                           handle handle_pc, success: non
 * 0,failed: 0
 */
CRTC_API HANDLE
crtc_pcf_create_peer_connection(HANDLE handle_pcf,
                                const crtc_rtc_configuration* config,
                                const crtc_pc_observer* observer,
                                int* error);

/**
 * @brief destroy peer_connection handle
 * @param handle_pc                         handle handle_pcf
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_pc_destroy(HANDLE handle_pc);

/**
 * @brief create media_stream handle handle_ms. call crtc_ms_destroy destroy
 * handle_ms
 * @param handle_pcf                        handle handle_pcf
 * @param stream_id                         media_stream id
 * @param error                             error code if failed
 * @return HANDLE                           handle handle_ms,  success: non
 * 0,failed: 0
 */
CRTC_API HANDLE crtc_pcf_create_local_media_stream(HANDLE handle_pcf,
                                                   const char* stream_id,
                                                   int* error);

/**
 * @brief create audio_source handle handle_as. call crtc_as_destroy destroy
 * handle_as
 * @param handle_pc                          handle handle_pcf
 * @param error                              error code if failed
 * @return HANDLE                            handle handle_as, success: non
 * 0,failed: 0
 */
CRTC_API HANDLE crtc_pcf_create_audio_source(HANDLE handle_pcf, int* error);

/**
 * @brief create audio_track handle handle_at. call crtc_at_destroy destroy
 * handle_at
 * @param handle_pcf                        handle_pcf
 * @param handle_as                         handle_as
 * @param label                             audio track label
 * @param error                             failed error code
 * @return HANDLE                           handle handle_vt, success: non 0,
 * failed: 0
 */
CRTC_API HANDLE crtc_pcf_create_audio_track(HANDLE handle_pcf,
                                            HANDLE handle_as,
                                            const char* label,
                                            int* error);

/**
 * @brief create video_track handle handle_vt. call crtc_vt_destroy destroy
 * handle_vt
 * @param handle_pcf                        handle_pcf
 * @param handle_as                         handle_as
 * @param label                             video track label
 * @return HANDLE                           handle handle_vt, success: non 0,
 * failed: 0
 */
CRTC_API HANDLE crtc_pcf_create_video_track(HANDLE handle_pcf,
                                            HANDLE handle_vs,
                                            const char* label,
                                            int* error);

#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_PEER_CONNECTION_FACTORY_H_
