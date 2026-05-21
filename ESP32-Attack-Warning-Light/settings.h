#pragma once
#include <Arduino.h>
#include "config.h"

// Runtime-configurable settings — loaded from NVS on boot, saved on web change.
// All reads/writes are safe without a mutex (8/32-bit aligned, ESP32 atomic).
extern uint8_t  g_brightness;
extern uint32_t g_alert_cooldown;
extern uint32_t g_deauth_thresh;
extern uint32_t g_beacon_thresh;
extern uint32_t g_probe_thresh;
extern uint32_t g_detect_window;
extern uint32_t g_channel_hop_ms;

// Set when the web UI changes the ambient mode; renderer_task clears it and
// triggers a crossfade exactly as the physical button does.
extern volatile bool g_web_mode_changed;

// Auto cycle — cycles randomly through ambient modes every g_random_dwell_ms.
// Not persisted; always starts false on boot.
extern volatile bool g_random_cycle;
extern uint32_t      g_random_dwell_ms;

void settings_load();
void settings_save();
void settings_reset_defaults();
void settings_save_mode(uint8_t mode);
