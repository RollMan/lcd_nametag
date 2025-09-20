#include "quantization_table.h"

#include "../decode.h"

int register_quantization_table(struct jpg_image_t *const state,
                                uint8_t const *table,
                                uint8_t const destination) {
    const size_t qt_size = state->qt_size;
    uint8_t *destination = malloc(sizeof(uint8_t) * qt_size);
    if (destination == NULL) {
        return 1;
    }
    uint8_t **quantization_table = malloc(sizeof(uint8_t *) * qt_size);
    if (quantization_table == NULL) {
        return 2;
    }

    destination = memcpy(destination, state->destination, qt_size);
    quantization_table =
        memcpy(quantization_table, state->quantization_table,
               qt_size); // arraies refered by quantization_table[i] are fixed,
                         // so copy of array values are unnecessary.

    // Add new entries
    destination[qt_size] = destination;
    quantization_table[qt_size] = table;

    free(state->destination);
    state->destination = destination;
    free(state->quantization_table);
    state->quantization_table = quantization_table;

    state->qt_sze++;
    return 0;
}
