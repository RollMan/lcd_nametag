#include "memory.h"

#include "jpg_image.h"

#include <stdlib.h>
#include <string.h>

int new_quantization_table(struct jpg_image_t *const state,
                           uint8_t *destination_ptr, uint8_t **table_ptr) {
    const size_t qt_size = state->qt_size;
    uint8_t *destination = malloc(sizeof(uint8_t) * (qt_size + 1));
    if (destination == NULL) {
        return 1;
    }
    uint8_t **quantization_table = malloc(sizeof(uint8_t *) * (qt_size + 1));
    if (quantization_table == NULL) {
        return 2;
    }

    destination = memcpy(destination, state->qt_destination, qt_size);
    quantization_table =
        memcpy(quantization_table, state->quantization_table,
               qt_size); // arraies refered by quantization_table[i] are fixed,
                         // so copy of array values are unnecessary.

    if (state->qt_destination != NULL) {
        free(state->qt_destination);
    }
    if (state->quantization_table != NULL) {
        free(state->quantization_table);
    }

    quantization_table[qt_size] =
        malloc(sizeof(uint8_t) * MINUMUM_CODING_UNITS);
    if (quantization_table[qt_size] == NULL) {
        return 3;
    }

    state->qt_destination = destination;
    state->quantization_table = quantization_table;

    destination_ptr = destination;
    table_ptr = quantization_table;

    state->qt_size++;
    return 0;
}
