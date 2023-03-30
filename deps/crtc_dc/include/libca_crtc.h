/**
 * @brief SDK global init and deinit.
 * @copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-02-29
 * @file libca_crtc.h
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

/**
 * @brief crtc init option used by @link crtc_init @endlink
 */
typedef struct crtc_init_option {
  /**
   * @brief enable custom adm or not. default 1 enabled.
   */
  int enable_custom_adm_ = 1;
} crtc_init_option;

/**
 * @brief crtc_debug sdk log config，this is global api
 * @param file_path                         log file path，if NULL, only output
 * to screen
 * @param level                             log output level，0 is the highest
 * level, output the most complete; 4 is not output log
 * @return void
 */
CRTC_API void crtc_debug(const char* file_path, crtc_e_debug_log_level level);

/**
 * @brief crtc_init sdk init，this is global api
 * @param option                            crtc_init_option
 * @return HANDLE                           engine handle_crtc, success：!0
 *                                          failed 0 (NULL)
 */
CRTC_API HANDLE crtc_init(crtc_init_option* option);

/**
 * @brief Deinitialize the SDK. This is a global API.
 * @param handle_crtc                       engine handle_crtc
 * @return int                              success：== 0，failed：< 0
 */
CRTC_API int crtc_deinit(HANDLE handle_crtc);

/**
 * @brief crtc_clean sdk clean，this is global api, only call once at app exit.
 * @return void
 */
CRTC_API void crtc_clean(void);

#ifdef __cplusplus
}
#endif

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_CRTC_H_
