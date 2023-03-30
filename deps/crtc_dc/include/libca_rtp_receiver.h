/**
 * @copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-02-04
 * @file libca_rtp_receiver.h
 * @brief rtp receiver c api
 */

#ifndef CRTC_CRTC_API_INCLUDE_LIBCA_RTP_RECEIVER_H_
#define CRTC_CRTC_API_INCLUDE_LIBCA_RTP_RECEIVER_H_

// clang-format off
#include "libca_common.h"
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif

/*
  rr means rtp_receiver object.
*/
/**
 * @brief rtp_receiver set media steam track object
 * @param handle_rr                         handle handle_rr
 * @param handle_mst                        handle_mst address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_rr_get_track(HANDLE handle_rr, HANDLE* handle_mst);

/**
 * @brief get rtp_receiver id
 * @param handle_rr                         handle handle_rr
 * @param id                                id address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_rr_get_id(HANDLE handle_rr, char id[256]);

/**
 * @brief get rtp_receiver media type
 * @param handle_rr                         handle handle_rr
 * @param type                              type address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_rr_get_media_type(HANDLE handle_rr, int* type);

/**
 * @brief Returns a list of media stream ids associated with this sender's
 * track. These are signalled in the SDP so that the remote side can associate
 * tracks.
 * @param stream_ids                        media stream ids string array
 * address pointer
 * @param count                             media track id address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_rr_get_stream_ids(HANDLE handle_rr,
                                    char stream_ids[64][256],
                                    int* count);

/**
 * @brief Returns a list of media stream ids associated with this sender's
 * track. These are signalled in the SDP so that the remote side can associate
 * tracks.
 * @param handle_ms                         media track handle array address
 * @param count                             media track id address pointer
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_rr_get_streams(HANDLE handle_rr,
                                 HANDLE handle_ms[64],
                                 int* count);

#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_RTP_RECEIVER_H_
