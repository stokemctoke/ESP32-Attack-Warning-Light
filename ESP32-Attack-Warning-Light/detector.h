#pragma once
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include "config.h"

extern volatile DeviceState g_device_state;
extern SemaphoreHandle_t    g_state_mutex;

// Initialises WiFi in promiscuous mode (no network connection).
void detector_init();

// FreeRTOS task entry point. Hops channels, counts frames, updates device state.
void detector_task(void* pvParameters);
