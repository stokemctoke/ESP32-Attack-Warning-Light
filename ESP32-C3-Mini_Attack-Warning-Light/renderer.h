#pragma once
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include "config.h"

extern volatile DeviceState g_device_state;
extern AmbientMode          g_ambient_mode;
extern SemaphoreHandle_t    g_state_mutex;

// Call once in setup() after FastLED is initialised.
void renderer_init();

// FreeRTOS task entry point. Drives LED strip and polls button.
void renderer_task(void* pvParameters);
