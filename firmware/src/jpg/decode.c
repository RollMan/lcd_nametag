#include "decode.h"

#include <stdint.h>
/**
 * Decode n Minimum Coding Units (MCU) of JPEG from pos.
 * @param buf A pointer to a JPEG data buffer continued from. This may
 *            refer PROGMEM.
 * @param n The number of MCUs to be decoded.
 * @param state Decoding state.
 */
char *decode_n_mcu(uint8_t const *buf, uint16_t const n,
                   struct jpgdec_state_t *const state) {
    if (state->decode_state == BEFORE_IMAGE_DATA) {
        // Decode until image data starts.
    } else if (state->decode_state == INSIDE_IMAGE_DATA) {
        // Continue decoding data
    } else {
        // Validate end of image.
    }
    return (char *)0; // TODO
}
