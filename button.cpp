#include "button.h"
#include <Preferences.h>

static uint32_t last_edge_ms = 0;
static bool     last_pin     = HIGH;
static bool     pending_mode = false;  // press queued during an alert
static bool     ack_pending  = false;

static void save_and_advance() {
    if (!xSemaphoreTake(g_state_mutex, pdMS_TO_TICKS(10))) return;
    AmbientMode next = (AmbientMode)((g_ambient_mode + 1) % AMBIENT_MODE_COUNT);
    g_ambient_mode = next;
    xSemaphoreGive(g_state_mutex);

    Preferences prefs;
    prefs.begin("awl", false);
    prefs.putUChar("mode", (uint8_t)next);
    prefs.end();

    ack_pending = true;
}

void button_init() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    Preferences prefs;
    prefs.begin("awl", true);
    uint8_t saved = prefs.getUChar("mode", AMBIENT_CANDLE);
    prefs.end();

    if (saved >= AMBIENT_MODE_COUNT) saved = AMBIENT_CANDLE;

    if (xSemaphoreTake(g_state_mutex, portMAX_DELAY)) {
        g_ambient_mode = (AmbientMode)saved;
        xSemaphoreGive(g_state_mutex);
    }
}

bool button_poll(DeviceState current_state) {
    bool pin = (bool)digitalRead(BUTTON_PIN);
    uint32_t now = millis();

    // Detect falling edge (active LOW, debounced)
    if (last_pin == HIGH && pin == LOW && (now - last_edge_ms) > DEBOUNCE_MS) {
        last_edge_ms = now;
        bool in_alert = (current_state != STATE_AMBIENT &&
                         current_state != STATE_TRANSITIONING);
        if (in_alert) {
            pending_mode = true;
        } else {
            save_and_advance();
        }
    }
    last_pin = pin;

    // Apply queued press once alert clears
    if (pending_mode &&
        (current_state == STATE_AMBIENT || current_state == STATE_TRANSITIONING)) {
        pending_mode = false;
        save_and_advance();
    }

    if (ack_pending) {
        ack_pending = false;
        return true;
    }
    return false;
}
