#include "morse.h"
#include <ctype.h>

MorseSymbol   g_morse_seq[MORSE_MAX_SYMBOLS];
uint16_t      g_morse_len     = 0;
uint16_t      g_morse_pos     = 0;
uint32_t      g_morse_next_ms = 0;
volatile bool g_morse_active  = false;
volatile bool g_morse_loop    = false;

volatile bool g_morse_pending      = false;
char          g_morse_pending_text[128] = {0};
volatile bool g_morse_pending_loop = false;

// ── Timing (ms) — standard international morse ────────────────────────────────
#define DOT_MS   100
#define DASH_MS  300
#define ELEM_MS  100   // gap between elements within a character
#define CHAR_MS  300   // gap between characters
#define WORD_MS  700   // gap between words
#define END_MS  1000   // silence at end before loop restarts

// ── Code table (A-Z then 0-9) ─────────────────────────────────────────────────
static const char* const MORSE_TABLE[] = {
    ".-",    "-...",  "-.-.",  "-..",   ".",     "..-.",  "--.",   "....",
    "..",    ".---",  "-.-",   ".-..",  "--",    "-.",    "---",   ".--.",
    "--.-",  ".-.",   "...",   "-",     "..-",   "...-",  ".--",   "-..-",
    "-.--",  "--..",                              // A-Z
    "-----", ".----", "..---", "...--", "....-",
    ".....", "-....", "--...", "---..", "----.",  // 0-9
};

static void push(uint16_t dur, bool on) {
    if (g_morse_len >= MORSE_MAX_SYMBOLS - 1) return;
    g_morse_seq[g_morse_len++] = { dur, on };
}

void morse_encode(const char* text, bool loop) {
    g_morse_len = 0;
    bool first = true;

    for (int i = 0; text[i]; i++) {
        char c = (char)toupper((unsigned char)text[i]);

        if (c == ' ') {
            // Upgrade the preceding letter-gap to a word-gap
            if (g_morse_len > 0 && !g_morse_seq[g_morse_len - 1].on) {
                g_morse_seq[g_morse_len - 1].duration_ms = WORD_MS;
            }
            continue;
        }

        const char* code = nullptr;
        if (c >= 'A' && c <= 'Z') code = MORSE_TABLE[c - 'A'];
        else if (c >= '0' && c <= '9') code = MORSE_TABLE[26 + (c - '0')];
        if (!code) continue;

        if (!first) push(CHAR_MS, false);
        first = false;

        for (int j = 0; code[j]; j++) {
            if (j > 0) push(ELEM_MS, false);
            push(code[j] == '.' ? DOT_MS : DASH_MS, true);
        }
    }

    push(END_MS, false);

    g_morse_loop    = loop;
    g_morse_pos     = 0;
    g_morse_next_ms = millis() + g_morse_seq[0].duration_ms;
    g_morse_active  = true;
}
