// BEGINNING OF FILE -----------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @file numeric_types.h
/// @desc Defines custom numeric types for primitive numbers for clarity of 
///       variable bit width.
/// @date 12 Jan 2011
/// @auth Gary Steelman
////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <cfloat>

/*
  Signed integer types
*/
#define sint8  signed char
#define sint16 signed short int
#define sint32 signed int

#ifndef __cplusplus
#define sint64 signed long long
#endif

// #define SINT8_MAX  SCHAR_MAX
// #define SINT16_MAX SHRT_MAX
// #define SINT32_MAX LONG_MAX
// #define SINT64_MAX 0

// #define SINT8_MIN  SCHAR_MIN
// #define SINT16_MIN SHRT_MIN
// #define SINT32_MIN LONG_MIN
// #define SINT64_MIN 0

#define SINT8_MAX  127
#define SINT16_MAX 32767
#define SINT32_MAX 2147483647
#define SINT64_MAX 9223372036854775807

#define SINT8_MIN  -128
#define SINT16_MIN -32768
#define SINT32_MIN -2147483648
#define SINT64_MIN –9223372036854775808

/*
  Unsigned integer types
*/
#define uint8  unsigned char
#define uint16 unsigned short int
#define uint32 unsigned int

#ifndef __cplusplus
#define uint64 unsigned long long
#endif

// #define UINT8_MAX  UCHAR_MAX
// #define UINT16_MAX USHRT_MAX
// #define UINT32_MAX ULONG_MAX
// #define UINT64_MAX 0

#ifdef  UINT8_MAX
#undef  UINT8_MAX
#define UINT8_MAX 255
#endif 

#ifndef UINT8_MAX
#define UINT8_MAX 255
#endif

#ifdef  UINT16_MAX
#undef  UINT16_MAX
#define UINT16_MAX 65535
#endif

#ifndef UINT16_MAX
#define UINT16_MAX 65535
#endif

#ifdef  UINT32_MAX
#undef  UINT32_MAX
#define UINT32_MAX 4294967295
#endif

#ifndef UINT32_MAX
#define UINT32_MAX 4294967295
#endif

#ifdef  UINT64_MAX
#undef  UINT64_MAX
#define UINT64_MAX 18446744073709551615
#endif

#ifndef UINT64_MAX
#define UINT64_MAX 18446744073709551615
#endif

#define UINT8_MIN  0
#define UINT16_MIN 0
#define UINT32_MIN 0
#define UINT64_MIN 0

/*
  Signed float types
*/
#define sfloat32  float 
#define sfloat64  double
#define sdouble64 double 

#define SFLOAT32_MAX  FLT_MAX
#define SFLOAT64_MAX  DBL_MAX
#define SDOUBLE64_MAX DBL_MAX

#define SFLOAT32_MIN  FLT_MIN
#define SFLOAT64_MIN  DBL_MIN
#define SDOUBLE64_MIN DBL_MIN

// END OF FILE -----------------------------------------------------------------
