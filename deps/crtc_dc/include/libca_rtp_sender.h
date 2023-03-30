/**
 * @copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-02-04
 * @file libca_rtp_sender.h
 * @brief rtp sender c api
 */

#ifndef CRTC_CRTC_API_INCLUDE_LIBCA_RTP_SENDER_H_
#define CRTC_CRTC_API_INCLUDE_LIBCA_RTP_SENDER_H_

// clang-format off
#include "libca_common.h"
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif

/*
  rs means rtp_sender object.
*/
/**
 * @brief rtp_receiver set media steam track object
 * @param handle_ms                         handle handle_ms
 * @param handle_mst                        handle handle_mst
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_rs_set_track(HANDLE handle_rs, HANDLE handle_mst);

/**
 * @biref rtp_receiver get media steam track object
 * @param handle_ms                         handle handle_ms
 * @param handle_mst                        handle handle_mst address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_rs_get_track(HANDLE handle_rs, HANDLE* handle_mst);

/**
 * @brief get rtp_sender id
 * @param handle_ms                         handle handle_ms
 * @param id                                id address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_rs_get_id(HANDLE handle_rs, char id[256]);

/**
 * @brief get rtp_sender media type
 * @param handle_ms                         handle handle_ms
 * @param id                                type address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_rs_get_media_type(HANDLE handle_rs, int* type);

/**
 * @brief a list of media stream ids associated with this sender's track.
 * @param handle_ms                         handle handle_ms
 * @param id                                ms_ids string array address pointer
 * @param count                             count address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_rs_get_stream_ids(HANDLE handle_rs,
                                    char ms_ids[64][256],
                                    int* count);

#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_RTP_SENDER_H_
