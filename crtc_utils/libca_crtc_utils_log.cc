/*
 * @Copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-03-06
 * @file libca_crtc_utils_log.cc
 */

#include "crtc_utils/libca_crtc_utils_log.h"

#include <stdarg.h>
#include <stdio.h>

namespace crtc {
void Log(int level,
         const char* file,
         int line,
         const char* func,
         const char* format,
         ...) {
  printf("level: %d ", level);
  printf("file: %s ", file);
  printf("func: %s ", func);
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
}
}  // namespace crtc
