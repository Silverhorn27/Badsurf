#pragma once  /* badsurflib/types.h */

#include <stddef.h>
#include <stdbool.h>

#ifdef __INT8_TYPE__
typedef __INT8_TYPE__ i8;
#endif
#ifdef __INT16_TYPE__
typedef __INT16_TYPE__ i16;
#endif
#ifdef __INT32_TYPE__
typedef __INT32_TYPE__ i32;
#endif
#ifdef __INT64_TYPE__
typedef __INT64_TYPE__ i64;
#endif
#ifdef __UINT8_TYPE__
typedef __UINT8_TYPE__ u8;
#endif
#ifdef __UINT16_TYPE__
typedef __UINT16_TYPE__ u16;
#endif
#ifdef __UINT32_TYPE__
typedef __UINT32_TYPE__ u32;
#endif
#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ u64;
#endif


// Generic pointer
typedef void* ptr;

// Generic pointer to objects/vars
typedef void* var;
#define var_cast(v, T)  (T*)(v)

// Type used for pointers to allocated memory
typedef void* memptr;

typedef u8 byte;
#define bytes(ptr)  (byte*)(ptr)  /* Cast pointer to bytes buffer type */
