/* @Copyright (c) 2019-2023 BJY. All rights reserved.
 * @author hhool
 * @date 2023-03-28
 * @file main.cc
 */

#include <libca_crtc_api.h>
#include "tests/libca_crtc_dc_unittest.h"
#include <gtest/gtest.h>


int main(int argc, char** argv) {
#if defined(_DEBUG) && defined(_MSC_VER) && defined(WIN32)
  int Flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
  Flag |= _CRTDBG_LEAK_CHECK_DF;
  _CrtSetDbgFlag(Flag);
  // _CrtSetBreakAlloc(593);
#endif
  testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  crtc_clean();
  return ret;
}
