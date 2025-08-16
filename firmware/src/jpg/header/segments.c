#include "segments.h"

#include "../binread.h"
#include "../decode.h"

// #ifndef AVR_SOMETHING // TODO
#include <stdio.h>

int decode_application_default_header(uint8_t const *buf,
                                      struct jpgdec_state_t *const state) {
    uint8_t const *const orig = buf;
    const uint16_t segment_length = READ_WORD(&buf);
    // Read (ignore) identifier
    for (; *buf; ++buf) {
        printf("%d\n", buf - orig);
    }
    printf("%d\n", buf - orig);

    // pass through NULL byte.
    buf++;
    printf("%d\n", buf - orig);

    // Read version
    buf += 2;

    // Read units
    state->density_units = READ_BYTE(buf);

    // Read density
    state->density_width = READ_WORD(&buf);
    state->density_height = READ_WORD(&buf);

    // Read thumbnail size
    uint8_t thumbnail_width = READ_BYTE(buf);
    uint8_t thumbnail_height = READ_BYTE(buf);

    // Read (ignore) thumbnail data.
    printf("%d\n", 3 * thumbnail_width * thumbnail_width);
    buf += 3 * thumbnail_width * thumbnail_width;
    if (buf - orig != segment_length) {
        printf("%d %d\n", buf - orig, segment_length);
        return 1;
    }
    return 0;
}
