#pragma once
#include "../common.h"

#include <stdint.h>
#include <stddef.h>

static const size_t MINUMUM_CODING_UNITS = 8 * 8;

struct jpg_image_t {
    decode_state_t decode_state;
    uint8_t density_units;
    uint16_t density_width;
    uint16_t density_height;
    size_t qt_size;
    uint8_t *qt_destination;
    uint8_t **quantization_table;
};
