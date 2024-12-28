#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <stdint.h>

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef float f32;
typedef double f64;

enum exit_code {
    EXT_SUCCESS,
    EXT_GLFW_INIT,
    EXT_VULKAN_SUPPORT,
    EXT_GLFW_WINDOW_CREATION,
    EXT_ARENA_ALLOCATION,
    EXT_ARENA_SIZE,
    EXT_VULKAN_INSTANCE,
    EXT_VULKAN_LAYERS,
    EXT_VULKAN_DEBUG_MESSENGER,
    EXT_VULKAN_DEVICE,
    EXT_VULKAN_QUEUE_FAMILIES,
    EXT_VULKAN_LOGICAL_DEVICE,
    EXT_VULKAN_SURFACE,
    EXT_VULKAN_SWAP_CHAIN_SUPPORT,
    NUM_EXT
};

#endif // PRIMITIVES_H
