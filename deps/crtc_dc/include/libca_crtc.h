/* @Copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-02-29
 * @file libca_crtc.h
 * @description SDK global init and deinit.
 */
#ifndef CRTC_CRTC_API_INCLUDE_LIBCA_CRTC_H_
#define CRTC_CRTC_API_INCLUDE_LIBCA_CRTC_H_

// clang-format off
#include "libca_common.h"
#include "libca_video_codec.h"
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif

enum crtc_e_debug_log_level {
  kLogLevelSensitive,
  kLogLevelVerbose,
  kLogLevelInfo,
  kLogLevelWarning,
  kLogLevelError,
  kLogLevelNone,
};

typedef struct crtc_init_option {
  /*
   * enable custom adm audio input output
   * default 1 true
   */
  int enable_custom_adm_ = 1;
} crtc_init_option;

/* @CRTC_API HANDLE crtc_debug();
 * SDK 日志配置 此接口是全局接口
 * @param file_path                         日志文件输出路径，若为 NULL
 * 则只输出到屏幕
 * @param level                             日志输出等级，0
 * 为最高级，输出最全；4 为不输出
 * @return 无
 */
CRTC_API void crtc_debug(const char* file_path, crtc_e_debug_log_level level);

/* @CRTC_API HANDLE crtc_init();
 * 初始化 SDK 此接口是全局接口
 * @param option                            crtc设置， 为空采用结构体默认设置
 * @return HANDLE                           引擎句柄handle_crtc, 成功：非
 *                                          0,失败 0 (NULL)
 */
CRTC_API HANDLE crtc_init(crtc_init_option* option);

/* @CRTC_API int crtc_deinit(HANDLE handle_crtc);
 * 反初始化 SDK 此接口是全局接口
 * @param handle_crtc                       引擎句柄
 * @return int                              调用成功：== 0，失败：< 0
 */
CRTC_API int crtc_deinit(HANDLE handle_crtc);

/* @CRTC_API int crtc_deinit(HANDLE handle_crtc);
 * 释放SDK使用的系统资源, 此接口是全局接口, 用于应用退出时调用
 * 只调用一次
 * @return void
 */
CRTC_API void crtc_clean(void);

#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_CRTC_H_
