#ifndef VULKAN_EXTENSION_H
#define VULKAN_EXTENSION_H

#include "core/common.h"

/* NOTE(spencer): This will hold all vulkan function pointers that aren't auto loaded
 * */

VkResult vkCreateDebugUtilsMessengerEXT(VkInstance instance,
                                        const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                        const VkAllocationCallbacks *pAllocator,
                                        VkDebugUtilsMessengerEXT *pDebugMessenger);

void vkDestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                     const VkAllocationCallbacks *pAllocator);

#endif // VULKAN_EXTENSION_H