#pragma once
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include "config.h"

extern volatile DeviceState  g_device_state;
extern SemaphoreHandle_t     g_state_mutex;

// Last completed detection-window snapshot — updated every g_detect_window ms.
// Written by detector_task; read by webserver handlers. Volatile uint32_t reads
// are atomic on ESP32, so no mutex is required.
extern volatile uint32_t g_last_deauth;
extern volatile uint32_t g_last_beacon;
extern volatile uint32_t g_last_probe;

// Initialises WiFi promiscuous mode. Call after WiFi.softAP() has started.
void detector_init();

// FreeRTOS task entry point. Hops channels, counts frames, updates device state.
void detector_task(void* pvParameters);
