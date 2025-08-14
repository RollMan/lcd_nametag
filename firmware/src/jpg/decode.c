#include "decode.h"

#include <stdint.h>

typedef enum {
    START_OF_IMAGE = 0xffd8,
    APPLICATION_DEFAULT_HEADER = 0xffe0,
    QUANTIZATION_TABLE = 0xffdb,
    START_OF_FRAME = 0xffc0,
    DEFINE_HUFFMAN_TABLE = 0xffc4,
    START_OF_SCAN = 0xffda,
    END_OF_IMAGE = 0xffd9,
} marker_mapping;

/**
 * Decode n Minimum Coding Units (MCU) of JPEG from pos.
 * @param buf A pointer to a JPEG data buffer continued from. This may
 *            refer PROGMEM.
 * @param n The number of MCUs to be decoded.
 * @param state Decoding state.
 */
char *decode_n_mcu(char const *const buf, uint16_t const n,
                   struct jpgdec_state_t const *const state) {
    if (state->decode_state == BEFORE_IMAGE_DATA) {
        // Decode until image data starts.
    } else if (state->decode_state == INSIDE_IMAGE_DATA) {
        // Continue decoding data
    } else {
        // Validate end of image.
    }
}
