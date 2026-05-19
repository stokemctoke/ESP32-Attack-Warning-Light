#include "config.h"
#include "detector.h"
#include "renderer.h"
#include "button.h"

// ── Shared state ──────────────────────────────────────────────────────────────
// Written by detector_task; read by renderer_task. Both access via g_state_mutex.
volatile DeviceState g_device_state = STATE_AMBIENT;
AmbientMode          g_ambient_mode  = AMBIENT_CANDLE;
SemaphoreHandle_t    g_state_mutex   = NULL;

void setup() {
    Serial.begin(115200);

    g_state_mutex = xSemaphoreCreateMutex();

    button_init();    // loads saved mode from flash
    renderer_init();  // FastLED + candle seed
    detector_init();  // WiFi promiscuous, no network connection

    // ESP32-C3 is single-core. Both tasks run on core 0 under FreeRTOS preemption.
    // Detector at higher priority so WiFi counter snapshots are timely.
    xTaskCreate(detector_task, "detector", 4096, NULL, 5, NULL);
    xTaskCreate(renderer_task, "renderer", 8192, NULL, 4, NULL);
}

void loop() {
    // Tasks own the main work. Suspend the Arduino loop permanently.
    vTaskDelay(portMAX_DELAY);
}
