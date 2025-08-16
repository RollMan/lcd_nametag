#ifndef __DECODE_H__
#define __DECODE_H__
#include <stdint.h>
/*
 * Enum to represent decoding state.
 * This decoder decodes JPEG by image data section (after start of scan section)
 * at once. Then image data is decoded successively. decode_state_t, therefore,
 * consists of before-image-data and after-image-data.
 */
typedef enum {
    BEFORE_IMAGE_DATA,
    INSIDE_IMAGE_DATA,
    AFTER_IMAGE_DATA
} decode_state_t;

struct jpgdec_state_t {
    decode_state_t decode_state;
    uint8_t density_units;
    uint16_t density_width;
    uint16_t density_height;
};

void print_state(struct jpgdec_state_t const *const state);

int decode_n_mcu(uint8_t const *buf, uint16_t const n,
                 struct jpgdec_state_t *const state);
#endif
