#pragma once
#include "internal/jpg_image.h"

#include <stdint.h>

extern const size_t MINUMUM_CODING_UNITS;

typedef struct jpg_image_t jpg_image;

void print_decode_state(jpg_image const *const state);

int decode_n_mcu(uint8_t const **buf, uint16_t const n, jpg_image *const state);

jpg_image *new_jpg_image();

void free_jpg_image(jpg_image *const state);
