/**
 * @copyright (c) 2019-2023 BJY. All rights reserved.
 * @file libca_common.h
 * @author hhool
 * @date 2023-02-27
 * @brief dynamic library encapsulation related macro definition
 */
#ifndef CRTC_CRTC_API_INCLUDE_LIBCA_COMMON_H_
#define CRTC_CRTC_API_INCLUDE_LIBCA_COMMON_H_

#if defined(_WIN32) || defined(__CYGWIN__)
#ifdef CRTC_EXPORT
#define CRTC_API __declspec(dllexport)
#elif CRTC_IMPORT
#define CRTC_API __declspec(dllimport)
#else
#define CRTC_API
#endif
#elif defined(__GNUC__) && (__GNUC__ >= 4) && !defined(__APPLE__) && \
    (defined(CRTC_EXPORT) || defined(CRTC_IMPORT))
#define CRTC_API __attribute__((visibility("default")))
#elif defined(__APPLE__) && (defined(CRTC_EXPORT) || defined(CRTC_IMPORT))
#define CRTC_API __attribute__((visibility("default")))
#else
#define CRTC_API
#endif  // __GNUC__

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef ASSERT
#define ASSERT(x) (void)0
#endif

#if !defined(_WIN32)
typedef void* HANDLE;
#else
#include <Windows.h>
#endif
#include "libca_basetypes.h"
#include "libca_stdbool.h"
#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_COMMON_H_
