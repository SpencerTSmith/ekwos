#ifndef RENDER_ALLOCATOR_H
#define RENDER_ALLOCATOR_H

#include "core/common.h"
#include "render/render_common.h"

// forward declaration
typedef struct RND_Context RND_Context;

typedef struct RND_Allocator RND_Allocator;
struct RND_Allocator {
    VkPhysicalDeviceMemoryProperties device_memory_props;
    VkDeviceMemory memory;
    u64 capacity;
    // Not sure about this... should it have this? Would make it simpler, only have to pass in the
    // allocator
    VkDevice logical;
};

// TODO(ss): actually implement management of memory on the allocator side instead of caller side
RND_Allocator rnd_allocator_create(RND_Context *rc, u64 initial_size);
void rnd_allocator_free(RND_Context *rc, RND_Allocator *allocator);

// Finds best memory type, etc, binds
void rnd_alloc_image(RND_Allocator *allocator, RND_Context *rc, VkImageCreateInfo info,
                     VkMemoryPropertyFlags memory_properties, VkImage *image,
                     VkDeviceMemory *memory);
void rnd_alloc_buffer(RND_Allocator *allocator, RND_Context *rc, VkBufferCreateInfo info,
                      VkMemoryPropertyFlags memory_properties, VkBuffer *buffer,
                      VkDeviceMemory *memory);

#endif // RENDER_ALLOCATOR_H
