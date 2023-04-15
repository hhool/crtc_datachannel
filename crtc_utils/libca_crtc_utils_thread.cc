/**
 * @copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-03-06
 * @file ibca_crtc_thread_utils.cc
 */

// clang-format off
#include "crtc_utils/libca_crtc_utils_thread.h"

#include <chrono>
#include <thread>
// clang-format on

namespace crtc {
void std_milis_time_sleep(uint64_t time_milis) {
  std::chrono::milliseconds dura(time_milis);
  std::this_thread::sleep_for(dura);
}

uint64_t std_milis_time_now() {
  uint64_t time_millis =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::system_clock::now().time_since_epoch())
          .count();
  return time_millis;
}
}  // namespace crtc
