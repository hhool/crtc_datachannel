/**
 * @copyright (c) 2019-2023 BJY. All rights reserved.
 * @file libca_video_writer.h
 * @author hhool
 * @date 2023-02-28
 * @brief video writer c api
 */

#ifndef CRTC_CRTC_API_INCLUDE_LIBCA_VIDEO_WRITER_H_
#define CRTC_CRTC_API_INCLUDE_LIBCA_VIDEO_WRITER_H_

// clang-format off
#include "libca_common.h"
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif

typedef enum crtc_video_type {
  kUnknown = 0,
  kI420 = 1,
  kIYUV = 2,
  kRGB24 = 3,
  kABGR = 4,
  kARGB = 5,
  kARGB4444 = 6,
  kRGB565 = 7,
  kARGB1555 = 8,
  kYUY2 = 9,
  kYV12 = 10,
  kUYVY = 11,
  kH264 = 12,
  kNV21 = 13,
  kNV12 = 14,
  kBGRA = 15,
} crtc_video_type;

typedef enum crtc_video_frame_rate {
  k30fps = 30,
  k24fps = 24,
  k20fps = 20,
  k15fps = 15,
  k10fps = 10,
  k5fps = 5,
} crtc_video_frame_rate;

/*
vs_cap means video source capturer object.
*/

typedef void (*Event_Vs_OnDispose)(HANDLE handle);
typedef struct crtc_vs_cap_observer {
  Event_Vs_OnDispose OnDispose_;
} crtc_vs_cap_observer;

CRTC_API
int crtc_vs_cap_set_observer(HANDLE handle, crtc_vs_cap_observer* callback);

/**
 * @brief create image writer handle
 * @param handle_crtc                   handle handle_cap
 * @param width                         image width
 * @param height                        image height
 * @param video_type                    image type
 * @param frame_rate                    image frame rate
 * @param is_screen                     !0：screen  , 0：camera
 * @return HANDLE                       success：> 0，failed：<= 0
 */
CRTC_API HANDLE crtc_vs_cap_create(HANDLE handle_crtc,
                                   int width,
                                   int height,
                                   crtc_video_type video_type,
                                   crtc_video_frame_rate frame_rate,
                                   int is_screen);

/**
 * @brief write image data
 * @param handle_cap                    handle handle_cap
 * @param data                          data of image
 * @param len                           length of image data
 * @param in_width                      width of image
 * @param in_height                     height of image
 * @param time_ms                       time_ms of image data
 * @return int                          success：0，failed：< 0
 */
CRTC_API int crtc_vs_cap_write(HANDLE handle_cap,
                               const void* data,
                               const int len,
                               uint32_t in_width,
                               uint32_t in_height,
                               long long time_ms);

/**
 * @brief destroy image writer handle
 * @param handle_cap                   handle handle_cap
 * @return void
 */
CRTC_API void crtc_vs_cap_destroy(HANDLE handle_cap);

/**
 * @brief update max framerate of image writer handle
 * @param handle_cap                handle handle_cap
 * @param max_framerate             max frame_rate
 * @return int                      success：0，failed：< 0
 */
CRTC_API int crtc_vs_cap_update_max_framerate(HANDLE handle_cap,
                                              int max_frame_rate);

#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_VIDEO_WRITER_H_
