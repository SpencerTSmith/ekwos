#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <string.h>

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef double f64;
typedef float f32;

#define thread_local _Thread_local
#define function_local static
#define translation_local static

// Nice little macros //
#define CLAMP(value, min, max) (((value) < (min)) ? (min) : ((value) > (max)) ? (max) : (value))
#define MAX(first, second) ((first) > (second) ? (first) : (second))
#define MIN(first, second) ((first) > (second) ? (second) : (first))

// adds the alignment and then masks the lower bits to get the next (higher) multiple of that
// alignment... binary math
#define ALIGN_ROUND_UP(x, b) (((x) + (b) - 1) & (~((b) - 1)))

#define PI 3.14159265358979323846
#define RADIANS(degrees) ((degrees) * (PI / 180))

#define STATIC_ARRAY_COUNT(arr) (sizeof(arr) / sizeof(arr[0]))

#define ZERO_STRUCT(ptr) (memset((ptr), 0, sizeof(*(ptr))))
#define ZERO_SIZE(ptr, size) (memset((ptr), 0, (size)))

#define VOID_PROC ((void)0)

#endif // COMMON_H
