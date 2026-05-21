#pragma once
#include <Arduino.h>

#define MORSE_MAX_SYMBOLS 640   // enough for ~40 average characters

struct MorseSymbol {
    uint16_t duration_ms;
    bool     on;
};

// Playback state — owned by renderer_task.
extern MorseSymbol   g_morse_seq[MORSE_MAX_SYMBOLS];
extern uint16_t      g_morse_len;
extern uint16_t      g_morse_pos;
extern uint32_t      g_morse_next_ms;
extern volatile bool g_morse_active;
extern volatile bool g_morse_loop;

// Pending request written by webserver handler, consumed by renderer_task.
// The renderer does the actual encode to avoid cross-task array access.
extern volatile bool g_morse_pending;
extern char          g_morse_pending_text[128];
extern volatile bool g_morse_pending_loop;

// Encodes text (A-Z, 0-9, spaces) and starts playback.
// Call only from renderer_task context.
void morse_encode(const char* text, bool loop);
