/* @Copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-02-04
 * @file libca_video_render.h
 * @description video render c api
 */

#ifndef CRTC_CRTC_API_INCLUDE_LIBCA_VIDEO_RENDER_H_
#define CRTC_CRTC_API_INCLUDE_LIBCA_VIDEO_RENDER_H_

// clang-format off
#include "libca_common.h"
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif
typedef void (*video_sink_on_frame)(const uint8_t* y,
                                    int stride_y,
                                    const uint8_t* u,
                                    int stride_u,
                                    const uint8_t* v,
                                    int stride_v,
                                    int width,
                                    int height,
                                    HANDLE context);

typedef struct crtc_video_sink {
  video_sink_on_frame OnFrame_;
  void* Context_;
} crtc_video_sink;

typedef struct crtc_video_sink_wants {
  bool rotation_applied_ = false;
  bool black_frames_ = false;
  int max_framerate_fps = 15;
} crtc_video_sink_wants;

/*
vsr means video sink render object.
*/

/** @CRTC_API HANDLE crtc_vsr_create(HANDLE handle_crtc,
                              const crtc_video_sink* sink,
                              const crtc_video_sink_wants* video_sink_wants);
 * 创建视频图像接收对象
 * @param handle_crtc                       句柄handle_crtc
 * @param sink                              crtc_video_sink 配置
 * @param video_sink_wants                  video_sink_wants 配置
 * @return HANDLE                           !0 成功, 0失败
 */
CRTC_API HANDLE crtc_vsr_create(HANDLE handle_crtc,
                                const crtc_video_sink* sink,
                                const crtc_video_sink_wants* video_sink_wants);

/** @CRTC_API HANDLE crtc_vsr_destroy(HANDLE handle_vsr);
 * 创建视频图像接收对象
 * @param handle_vsr                        句柄handle_vsr
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_vsr_destroy(HANDLE handle_vsr);

#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_VIDEO_RENDER_H_
