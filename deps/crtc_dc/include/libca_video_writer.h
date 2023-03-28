/* @Copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-02-28
 * @file libca_video_writer.h
 * @description video writer c api
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
 * @CRTC_API HANDLE crtc_vs_cap_create(HANDLE handle_crtc,
                                 int width,
                                 int height,
                                 crtc_video_type video_type,
                                 crtc_video_frame_rate frame_rate);
 * 创建图像数据写入句柄
 * @param[in] handle_crtc                   引擎实例句柄
 * @param[in] width                         视频分辨率 宽
 * @param[in] height                        视频分辨率 高
 * @param[in] video_type                    视频格式类型
 * @param[in] frame_rate                    视频帧率
 * @param[in] is_screen                     !0：桌面采集, 0：非桌面采集
 * @return HANDLE                           创建成功 (>0)
 * 返回值为创建的实例句柄,
 *                                          <=0 创建失败
 */
CRTC_API HANDLE crtc_vs_cap_create(HANDLE handle_crtc,
                                   int width,
                                   int height,
                                   crtc_video_type video_type,
                                   crtc_video_frame_rate frame_rate,
                                   int is_screen);

/**
 * @int crtc_vs_cap_write(HANDLE handle_cap,
 *                        const void* data,
 *                        const int len,
 *                        long long time_ms)
 * 写入图像数据
 * @param[in] handle_cap                    实例句柄
 * @param[in] data                          图像数据
 * @param[in] len                           图像数据长度
 * @param[in] in_width                      图像数据宽
 * @param[in] in_height                     图像数据高
 * @param[in] time_ms                       图像数据被采集到时的毫秒时间
 * @return int                              写入成功(==0), <0 写入失败.
 */
CRTC_API int crtc_vs_cap_write(HANDLE handle_cap,
                               const void* data,
                               const int len,
                               uint32_t in_width,
                               uint32_t in_height,
                               long long time_ms);

/**
 * @void crtc_vs_cap_destroy(HANDLE handle_cap)
 * 销毁图像写入
 * @param[in] capturer                  实例句柄
 * @return                              无
 */
CRTC_API void crtc_vs_cap_destroy(HANDLE handle_cap);

/**
 * @int crtc_vs_cap_update_max_framerate(HANDLE handle_cap, int max_framerate)
 * 更新采集源的最大采集帧率
 * @param[in] handle_cap                采集源的实例句柄
 * @param[in] max_framerate             要更新的最大帧率
 * @return int                          成功(==0), <0 失败.
 */
CRTC_API int crtc_vs_cap_update_max_framerate(HANDLE handle_cap,
                                              int max_framerate);

#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_VIDEO_WRITER_H_
