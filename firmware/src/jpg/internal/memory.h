#pragma once
#include "jpg_image.h"
int new_quantization_table(struct jpg_image_t *const state,
                           uint8_t **destination_ptr, uint8_t ***table_ptr);
