#pragma once
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include "config.h"

extern volatile DeviceState g_device_state;
extern AmbientMode          g_ambient_mode;
extern SemaphoreHandle_t    g_state_mutex;

// Call once in setup() after g_state_mutex is created.
void button_init();

// Call each renderer frame. Returns true when a mode change was confirmed
// (caller should trigger the 150ms white ACK flash).
bool button_poll(DeviceState current_state);
