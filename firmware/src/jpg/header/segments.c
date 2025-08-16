#include "segments.h"

#include "../binread.h"
#include "../decode.h"

int decode_application_default_header(uint8_t const *buf,
                                      struct jpgdec_state_t *const state) {
    // Read (ignore) identifier
    for (; *buf; ++buf) {
    }

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
    buf += 3 * thumbnail_width * thumbnail_width;
    return 0;
}
