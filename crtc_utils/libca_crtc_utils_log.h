/**
 * @copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-03-06
 * @file libca_crtc_utils_log.h
 */

#ifndef CRTC_CRTC_UTILS_LIBCA_CRTC_UTILS_LOG_H_
#define CRTC_CRTC_UTILS_LIBCA_CRTC_UTILS_LOG_H_

// c99 LOG macro define

#define LOG_LEVEL_EMERG 0   /* system is unusable */
#define LOG_LEVEL_ALERT 1   /* action must be taken immediately */
#define LOG_LEVEL_CRIT 2    /* critical conditions */
#define LOG_LEVEL_ERR 3     /* error conditions */
#define LOG_LEVEL_WARNING 4 /* warning conditions */
#define LOG_LEVEL_NOTICE 5  /* normal but significant condition */
#define LOG_LEVEL_INFO 6    /* informational */
#define LOG_LEVEL_DEBUG 7   /* debug-level messages */

namespace crtc {
void Log(int level,
         const char* file,
         int line,
         const char* func,
         const char* format,
         ...);
}  // namespace crtc

#define LOG(level, fmt, ...)                                                \
  do {                                                                      \
    crtc::Log(level, __FILE__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__); \
  } while (0)

#define LOG_EMERG(fmt, ...) LOG(LOG_LEVEL_EMERG, fmt, ##__VA_ARGS__)
#define LOG_ALERT(fmt, ...) LOG(LOG_LEVEL_ALERT, fmt, ##__VA_ARGS__)
#define LOG_CRIT(fmt, ...) LOG(LOG_LEVEL_CRIT, fmt, ##__VA_ARGS__)
#define LOG_ERR(fmt, ...) LOG(LOG_LEVEL_ERR, fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...) LOG(LOG_LEVEL_WARNING, fmt, ##__VA_ARGS__)
#define LOG_NOTICE(fmt, ...) LOG(LOG_LEVEL_NOTICE, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) LOG(LOG_LEVEL_INFO, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) LOG(LOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__)

#endif  // CRTC_CRTC_UTILS_LIBCA_CRTC_UTILS_LOG_H_
