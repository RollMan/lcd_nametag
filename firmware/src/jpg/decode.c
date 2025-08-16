#include "decode.h"

#include "header.h"

#include <stdint.h>
#include <stdio.h> /* TODO: remove after test and get along somehow */
/**
 * Decode n Minimum Coding Units (MCU) of JPEG from pos.
 * @param buf A pointer to a JPEG data buffer continued from. This may
 *            refer PROGMEM.
 * @param n The number of MCUs to be decoded.
 * @param state Decoding state.
 */
int decode_n_mcu(uint8_t const *buf, uint16_t const n,
                 struct jpgdec_state_t *const state) {
    if (state->decode_state == BEFORE_IMAGE_DATA) {
        // Decode until image data starts.
        int ret = decode_header(buf, state);
        if (ret != 0) {
            return ret;
        }
    } else if (state->decode_state == INSIDE_IMAGE_DATA) {
        // Continue decoding data
    } else {
        // Validate end of image.
    }
    return 0; // TODO
}

void print_state(struct jpgdec_state_t const *const state) {
    printf("decode_state=%d, density_units=%d, density_width=%d, "
           "density_height=%d\n",
           state->decode_state, state->density_units, state->density_width,
           state->density_height);
}
