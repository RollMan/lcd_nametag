#include "segments.h"

#include "../../../debug.h"
#include "../binread.h"
#include "../jpg_image.h"
#include "memory.h"
#include "quantization_table.h"

#include <stdlib.h>

int decode_application_default_header(uint8_t const **buf,
                                      struct jpg_image_t *const state) {
    uint8_t const *const orig = *buf;
    const uint16_t segment_length = READ_WORD(buf);
    // Read (ignore) identifier
    for (; **buf; ++(*buf)) {
    }

    // pass through NULL byte.
    (*buf)++;

    // Read version
    (*buf) += 2;

    // Read units
    state->density_units = READ_BYTE(buf);

    // Read density
    state->density_width = READ_WORD(buf);
    state->density_height = READ_WORD(buf);

    // Read thumbnail size
    uint8_t thumbnail_width = READ_BYTE(buf);
    uint8_t thumbnail_height = READ_BYTE(buf);

    // Read (ignore) thumbnail data.
    (*buf) += 3 * thumbnail_width * thumbnail_width;
    if (*buf - orig != segment_length) {
        return 1;
    }
    return 0;
}

int decode_quantization_table(uint8_t const **buf,
                              struct jpg_image_t *const state) {
    uint8_t const *const orig = *buf;
    const uint16_t segment_length = READ_WORD(buf);
    {
        uint8_t *const destination;
        uint8_t **const quantization_table;
        int ret =
            new_quantization_table(state, &destination, &quantization_table);
        if (ret != 0) {
            return 1;
        }
        *destination = READ_BYTE(buf);
        for (int i = 0; i < MINUMUM_CODING_UNITS; i++) {
            (*quantization_table)[i] = READ_BYTE(buf);
        }
    }
    if (*buf - orig != segment_length) {
        return 1;
    }
    return 0;
}
