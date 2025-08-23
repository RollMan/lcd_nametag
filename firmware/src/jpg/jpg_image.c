#include "internal/jpg_image.h"

#include "../debug.h"
#include "internal/header.h"

#include <stdint.h>
#include <stdio.h> /* TODO: remove after test and get along somehow */
/**
 * Decode n Minimum Coding Units (MCU) of JPEG from pos.
 * @param buf A pointer to a JPEG data buffer continued from. This may
 *            refer PROGMEM.
 * @param n The number of MCUs to be decoded.
 * @param state Decoding state.
 */
int decode_n_mcu(uint8_t const **buf, uint16_t const n,
                 struct jpg_image_t *const state) {
    if (state->decode_state == BEFORE_IMAGE_DATA) {
        // Decode until image data starts.
        int ret = decode_header(buf, state);
        if (ret != 0) {
            return ret;
        }
        state->decode_state = INSIDE_IMAGE_DATA;
        // TODO: do decode data
    } else if (state->decode_state == INSIDE_IMAGE_DATA) {
        // Continue decoding data
    } else {
        // Validate end of image.
    }
    return 0; // TODO
}

void print_state(struct jpg_image_t const *const state) {
    DEBUG_PRINTF("decode_state=%d, density_units=%d, density_width=%d, "
                 "density_height=%d\n",
                 state->decode_state, state->density_units,
                 state->density_width, state->density_height);

    for (int table_idx = 0; table_idx < state->qt_size; table_idx++) {
        printf("quantization_table %d (%d):\n", table_idx + 1,
               state->qt_destination[table_idx]);
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                printf("%02x",
                       state->quantization_table[table_idx]
                                                [j + i * MINUMUM_CODING_UNITS]);
                if (j < MINUMUM_CODING_UNITS - 1) {
                    printf(" ");
                }
            }
            printf("\n");
        }
    }
}
