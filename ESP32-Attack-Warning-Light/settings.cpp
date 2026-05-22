#include "settings.h"
#include <Preferences.h>

uint8_t  g_brightness     = DEFAULT_BRIGHTNESS;
uint8_t  g_custom_r       = DEFAULT_CUSTOM_R;
uint8_t  g_custom_g       = DEFAULT_CUSTOM_G;
uint8_t  g_custom_b       = DEFAULT_CUSTOM_B;
uint32_t g_alert_cooldown = DEFAULT_ALERT_COOLDOWN;
uint32_t g_deauth_thresh  = DEFAULT_DEAUTH_THRESHOLD;
uint32_t g_beacon_thresh  = DEFAULT_BEACON_THRESHOLD;
uint32_t g_probe_thresh   = DEFAULT_PROBE_THRESHOLD;
uint32_t g_detect_window  = DEFAULT_DETECTION_WINDOW;
uint32_t g_channel_hop_ms = DEFAULT_CHANNEL_HOP_MS;

volatile bool g_web_mode_changed = false;

volatile bool g_random_cycle    = false;
uint32_t      g_random_dwell_ms = 30000;

void settings_load() {
    Preferences prefs;
    prefs.begin("awl", true);
    g_brightness     = prefs.getUChar("brightness", DEFAULT_BRIGHTNESS);
    g_custom_r       = prefs.getUChar("cr",         DEFAULT_CUSTOM_R);
    g_custom_g       = prefs.getUChar("cg",         DEFAULT_CUSTOM_G);
    g_custom_b       = prefs.getUChar("cb",         DEFAULT_CUSTOM_B);
    g_alert_cooldown = prefs.getUInt ("cooldown",   DEFAULT_ALERT_COOLDOWN);
    g_deauth_thresh  = prefs.getUInt ("deauth_t",   DEFAULT_DEAUTH_THRESHOLD);
    g_beacon_thresh  = prefs.getUInt ("beacon_t",   DEFAULT_BEACON_THRESHOLD);
    g_probe_thresh   = prefs.getUInt ("probe_t",    DEFAULT_PROBE_THRESHOLD);
    g_detect_window  = prefs.getUInt ("det_win",    DEFAULT_DETECTION_WINDOW);
    g_channel_hop_ms = prefs.getUInt ("hop_ms",     DEFAULT_CHANNEL_HOP_MS);
    g_random_dwell_ms= prefs.getUInt ("dwell_ms",   30000);
    prefs.end();
}

void settings_save() {
    Preferences prefs;
    prefs.begin("awl", false);
    prefs.putUChar("brightness", g_brightness);
    prefs.putUChar("cr",         g_custom_r);
    prefs.putUChar("cg",         g_custom_g);
    prefs.putUChar("cb",         g_custom_b);
    prefs.putUInt ("cooldown",   g_alert_cooldown);
    prefs.putUInt ("deauth_t",   g_deauth_thresh);
    prefs.putUInt ("beacon_t",   g_beacon_thresh);
    prefs.putUInt ("probe_t",    g_probe_thresh);
    prefs.putUInt ("det_win",    g_detect_window);
    prefs.putUInt ("hop_ms",     g_channel_hop_ms);
    prefs.putUInt ("dwell_ms",   g_random_dwell_ms);
    prefs.end();
}

void settings_reset_defaults() {
    g_brightness     = DEFAULT_BRIGHTNESS;
    g_custom_r       = DEFAULT_CUSTOM_R;
    g_custom_g       = DEFAULT_CUSTOM_G;
    g_custom_b       = DEFAULT_CUSTOM_B;
    g_alert_cooldown = DEFAULT_ALERT_COOLDOWN;
    g_deauth_thresh  = DEFAULT_DEAUTH_THRESHOLD;
    g_beacon_thresh  = DEFAULT_BEACON_THRESHOLD;
    g_probe_thresh   = DEFAULT_PROBE_THRESHOLD;
    g_detect_window  = DEFAULT_DETECTION_WINDOW;
    g_channel_hop_ms = DEFAULT_CHANNEL_HOP_MS;
    settings_save();
}

void settings_save_mode(uint8_t mode) {
    Preferences prefs;
    prefs.begin("awl", false);
    prefs.putUChar("mode", mode);
    prefs.end();
}
