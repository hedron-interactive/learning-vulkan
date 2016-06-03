// VulkanHeadless.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vulkan.h"

int print_result(VkResult result, const char *invocation) {
  switch (result) {
    case VK_SUCCESS:
      printf("%s --> VK_SUCCESS", invocation);
      return 1;
    case VK_ERROR_OUT_OF_HOST_MEMORY:
      printf("%s --> VK_ERROR_OUT_OF_HOST_MEMORY", invocation);
      return 0;
    case VK_ERROR_OUT_OF_DEVICE_MEMORY:
      printf("%s --> VK_ERROR_OUT_OF_DEVICE_MEMORY", invocation);
      return 0;
    case VK_ERROR_INITIALIZATION_FAILED:
      printf("%s --> VK_ERROR_INITIALIZATION_FAILED", invocation);
      return 0;
    case VK_ERROR_LAYER_NOT_PRESENT:
      printf("%s --> VK_ERROR_LAYER_NOT_PRESENT", invocation);
      return 0;
    case VK_ERROR_EXTENSION_NOT_PRESENT:
      printf("%s --> VK_ERROR_EXTENSION_NOT_PRESENT", invocation);
      return 0;
    case VK_ERROR_INCOMPATIBLE_DRIVER:
      printf("%s --> K_ERROR_INCOMPATIBLE_DRIVER", invocation);
      return 0;
    default:
      printf("%s --> Unknown error: %d", invocation, result);
      return 0;
  }
}

int main() {
  VkInstanceCreateInfo createInfo;
  VkApplicationInfo appInfo;
  memset(&createInfo, 0, sizeof(createInfo));
  memset(&appInfo, 0, sizeof(appInfo));
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Vulkan Headless";
  appInfo.applicationVersion = 1;
  appInfo.pEngineName = "V-Tachyon";
  appInfo.engineVersion = 1;

  VkInstance instance;
  if (!print_result(vkCreateInstance(&createInfo, nullptr, &instance), "vkCreateInstance")) {
    return 1;
  }

  uint32_t physical_device_count = 0;
  if (!print_result(vkEnumeratePhysicalDevices(instance, &physical_device_count, nullptr), "vkEnumeratePhysicalDevices")) {
    vkDestroyInstance(instance, nullptr);
    return 1;
  }

  printf("physical device count: %d", physical_device_count);
  vkDestroyInstance(instance, nullptr);
  return 0;
}

