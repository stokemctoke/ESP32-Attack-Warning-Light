#include "config.h"
#include "settings.h"
#include "detector.h"
#include "renderer.h"
#include "button.h"
#include "webserver.h"

// ── Shared state ──────────────────────────────────────────────────────────────
// Written by detector_task; read by renderer_task. Both access via g_state_mutex.
volatile DeviceState g_device_state = STATE_AMBIENT;
AmbientMode          g_ambient_mode  = AMBIENT_CANDLE;
SemaphoreHandle_t    g_state_mutex   = NULL;

void setup() {
    Serial.begin(115200);

    g_state_mutex = xSemaphoreCreateMutex();

    settings_load();   // load NVS settings before anything reads them
    button_init();     // loads saved mode from flash, sets g_ambient_mode
    webserver_init();  // WiFi AP + HTTP server (must run before detector_init)
    renderer_init();   // FastLED + candle seed
    detector_init();   // WiFi promiscuous (WiFi already running from webserver_init)

    // ESP32-C3 is single-core. All tasks run on core 0 under FreeRTOS preemption.
    // Detector at highest priority so WiFi counter snapshots are timely.
    xTaskCreate(detector_task, "detector", 4096, NULL, 5, NULL);
    xTaskCreate(renderer_task, "renderer", 8192, NULL, 4, NULL);
    // webserver_task is created inside webserver_init() at priority 3.
}

void loop() {
    // Tasks own the main work. Suspend the Arduino loop permanently.
    vTaskDelay(portMAX_DELAY);
}
