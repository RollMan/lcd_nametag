#pragma once
#include "jpg_image.h"

#include <stdint.h>
int decode_header(uint8_t const **, struct jpg_image_t *const);
