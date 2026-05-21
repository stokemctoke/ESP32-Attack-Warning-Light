#pragma once

// ── Hardware (compile-time only — change here and reflash) ────────────────────
#define LED_PIN         8       // GPIO to WS2812B data line
#define LED_COUNT       10      // change to match actual strip length
#define BUTTON_PIN      9       // mode-cycle button (pull-up, active LOW)

// ── Runtime-configurable defaults (loaded from NVS; web UI can override) ──────
#define DEFAULT_BRIGHTNESS          80      // 0-255; keep low on USB power
#define DEFAULT_WIFI_CHANNEL        6       // AP and initial scan channel (1-13)
#define DEFAULT_ALERT_COOLDOWN      10000   // ms to stay in alert after last detection
#define DEFAULT_DEAUTH_THRESHOLD    15      // deauth/disassoc frames per window (genuine attacks exceed 50/s)
#define DEFAULT_BEACON_THRESHOLD    100     // beacon frames per window (multi-SSID routers push baseline high)
#define DEFAULT_PROBE_THRESHOLD     30      // probe request frames per window (phones scanning spike this)
#define DEFAULT_DETECTION_WINDOW    2000    // ms rolling window for frame counting
#define DEFAULT_CHANNEL_HOP_MS      200     // ms between channel hops (1-13)

// ── Button ────────────────────────────────────────────────────────────────────
#define DEBOUNCE_MS     50

// ── Shared enums ──────────────────────────────────────────────────────────────
enum DeviceState : uint8_t {
    STATE_AMBIENT,
    STATE_ALERT_DEAUTH,
    STATE_ALERT_BEACON,
    STATE_ALERT_PROBE,
    STATE_ALERT_MULTI,
    STATE_TRANSITIONING   // crossfading back to ambient; managed by renderer only
};

enum AmbientMode : uint8_t {
    AMBIENT_CANDLE = 0,   // default on first boot
    AMBIENT_RAINBOW,
    AMBIENT_BREATHE,
    AMBIENT_FOREST,
    AMBIENT_OCEAN,
    AMBIENT_KITT,         // bouncing scanner with fading tail
    AMBIENT_RADIAL,       // radial breathe with centre-out wave and lag
    AMBIENT_PLASMA,       // layered sine fields mapped to lava palette
    AMBIENT_ARC,          // random blue-white electrical spark bursts
    AMBIENT_FIRE,         // perlin noise red fire — coherent flame body
    AMBIENT_MODE_COUNT    // sentinel for wrap-around
};
