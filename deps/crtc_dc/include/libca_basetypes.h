/**
 * @copyright (c) 2019-2023 BJY. All rights reserved.
 * @file libca_basetypes.h
 * @author hhool
 * @date 2022-09-03
 * @brief multi platform base types
 */
#ifndef CRTC_CRTC_API_INCLUDE_LIBCA_BASETYPES_H_
#define CRTC_CRTC_API_INCLUDE_LIBCA_BASETYPES_H_

#include <sys/types.h>

#ifndef _MSC_VER
// stdint.h is part of C99 but MSVC doesn't have it.
#include <stdint.h>  // For intptr_t.
#endif

/* define int types*/
#if defined(__GNUC__)

#ifndef _STDINT_H

/* FreeBSD has these C99 int types defined in /sys/inttypes.h already */
#ifndef _SYS_TYPES_H
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
#else
typedef u_int8_t uint8_t;
typedef u_int16_t uint16_t;
typedef u_int32_t uint32_t;
typedef u_int64_t uint64_t;
#endif  // _SYS_TYPES_H

#endif  // _STDINT_H

#elif defined(_MSC_VER)
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed __int64 int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned __int64 uint64_t;
#endif  // COMPILER_GCC/COMPILER_MSVC

#endif  // CRTC_CRTC_API_INCLUDE_LIBCA_BASETYPES_H_
