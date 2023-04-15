/**
* @copyright (c) 2019-2023 BJY. All rights reserved.
* @author hhool
* @date 2023-03-06
* @file libca_crtc_utils_thread.h
*/

#ifndef CRTC_CRTC_UTILS_LIBCA_CRTC_UTILS_THREAD_H_
#define CRTC_CRTC_UTILS_LIBCA_CRTC_UTILS_THREAD_H_

#include <cstdint>

namespace crtc {
void std_milis_time_sleep(uint64_t time_milis);
uint64_t std_milis_time_now();
}  // namespace crtc

#endif  // CRTC_CRTC_UTILS_LIBCA_CRTC_UTILS_THREAD_H_
