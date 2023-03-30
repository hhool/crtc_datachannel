/**
 * @copyright (c) 2019-2023 BJY. All rights reserved.
 * @file libca_stdbool.h
 * @author hhool
 * @date 2022-09-03
 * @brief stdbool.h for c
 */
#ifndef CRTC_CRTC_API_INCLUDE_LIBCA_STDBOOL_H_
#define CRTC_CRTC_API_INCLUDE_LIBCA_STDBOOL_H_

#ifndef __cplusplus

/* Even in pure C, we still need a standard boolean typedef */
#ifndef bool
typedef unsigned char bool;
#endif
// #define true    1
// #define false   0
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif

// typedef int _Bool;
// #define bool _Bool
//
// #define true 1
// #define false 0

#endif /* !__cplusplus */

#define __bool_true_false_are_defined 1

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_STDBOOL_H_
