#pragma once

// Starts WiFi AP ("AttackLight") and HTTP configuration server on port 80.
// Creates its own FreeRTOS task — call once from setup(), after g_state_mutex
// is created and settings_load() has run, but before detector_init().
void webserver_init();
