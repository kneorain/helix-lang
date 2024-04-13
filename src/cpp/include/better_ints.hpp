#pragma once

#include <cstdint>
#include <vcruntime.h>

#if _VCRT_COMPILER_PREPROCESSOR

#pragma warning(push)
#pragma warning(disable: _VCRUNTIME_DISABLED_WARNINGS)

typedef signed char        i8;
typedef short              i16;
typedef int                i32;
typedef long long          i64;
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

typedef signed char        i8_fast;
typedef int                i16_fast;
typedef int                i32_fast;
typedef long long          i64_fast;
typedef unsigned char      u8_fast;
typedef unsigned int       u16_fast;
typedef unsigned int       u32_fast;
typedef unsigned long long u64_fast;

typedef long long          isize_max;
typedef unsigned long long usize_max;

// These macros must exactly match those in the Windows SDK's intsafe.h.
#define I8_MIN  (-127i8 - 1)
#define I16_MIN (-32767i16 - 1)
#define I32_MIN (-2147483647i32 - 1)
#define I64_MIN (-9223372036854775807i64 - 1)
#define I8_MAX  127i8
#define I16_MAX 32767i16
#define I32_MAX 2147483647i32
#define I64_MAX 9223372036854775807i64
#define U8_MAX  0xffui8
#define U16_MAX 0xffffui16
#define U32_MAX 0xffffffffui32
#define U64_MAX 0xffffffffffffffffui64

#define I8_FAST_MIN   I8_MIN
#define I16_FAST_MIN  I32_MIN
#define I32_FAST_MIN  I32_MIN
#define I64_FAST_MIN  I64_MIN
#define I8_FAST_MAX   I8_MAX
#define I16_FAST_MAX  I32_MAX
#define I32_FAST_MAX  I32_MAX
#define I64_FAST_MAX  I64_MAX
#define U8_FAST_MAX   U8_MAX
#define U16_FAST_MAX  U32_MAX
#define U32_FAST_MAX  U32_MAX
#define U64_FAST_MAX  U64_MAX

#ifdef _WIN64
    #define IPTR_MIN  I64_MIN
    #define IPTR_MAX  I64_MAX
    #define UPTR_MAX  U64_MAX
#else
    #define IPTR_MIN  I32_MIN
    #define IPTR_MAX  I32_MAX
    #define UPTR_MAX  U32_MAX
#endif

#define IMAX_MIN      I64_MIN
#define IMAX_MAX      I64_MAX
#define UMAX_MAX      U64_MAX

#ifndef PTRDIFF_MIN
    #define PTRDIFF_MIN   IPTR_MIN
#endif

#ifndef PTRDIFF_MAX
    #define PTRDIFF_MAX   IPTR_MAX
#endif

#ifndef SIZE_MAX
    #ifdef _WIN64
        #define SIZE_MAX 0xffffffffffffffffui64
    #else
        #define SIZE_MAX 0xffffffffui32
    #endif
#endif

#ifndef SIG_ATOMIC_MIN
    #define SIG_ATOMIC_MIN I32_MIN
#endif

#ifndef SIG_ATOMIC_MAX
    #define SIG_ATOMIC_MAX I32_MAX
#endif

#ifndef WCHAR_MIN
    #define WCHAR_MIN 0x0000
#endif

#ifndef WCHAR_MAX
    #define WCHAR_MAX 0xffff
#endif

#ifndef WI_MIN
    #define WI_MIN 0x0000
#endif

#ifndef WI_MAX
    #define WI_MAX 0xffff
#endif

#define I8_C(x)   (x)
#define I16_C(x)  (x)
#define I32_C(x)  (x)
#define I64_C(x)  (x ## LL)

#define U8_C(x)   (x)
#define U16_C(x)  (x)
#define U32_C(x)  (x ## U)
#define U64_C(x)  (x ## ULL)

#define IMAX_C(x) I64_C(x)
#define UMAX_C(x) U64_C(x)

#endif // _VCRT_COMPILER_PREPROCESSOR
