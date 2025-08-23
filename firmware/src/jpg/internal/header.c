#include "header.h"

#include "../../debug.h"
#include "binread.h"
#include "header/segments.h"
#include "jpg_image.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

int decode_before_sof(uint8_t const **buf, struct jpg_image_t *const state) {
    uint16_t start_of_image = READ_WORD(buf);
    if (start_of_image != START_OF_IMAGE) {
        return 1;
    }
    uint8_t const *const orig = *buf;
    while (1) {
        const uint16_t marker = READ_WORD(buf);
        switch (marker) {
        case APPLICATION_DEFAULT_HEADER: {
            int ret = decode_application_default_header(buf, state);
            if (ret != 0) {
                return 1;
            }
        } break;
        case START_OF_SCAN:
            return 0;
        case COMMENT: {
            const uint16_t segment_length = READ_WORD(buf);
            SKIP_SEGLEN(buf, (size_t)segment_length);
        } break;
        case QUANTIZATION_TABLE: {
            int ret = decode_quantization_table(buf, state);
            if (ret != 0) {
                return 2;
            }
        } break;
        case END_OF_IMAGE:
            // Unexpected END_OF_IMAGE.
            return -1;
        default: {
            const uint16_t segment_length = READ_WORD(buf);
            DEBUG_PRINTF("Untreated marker: %x, seglen: %d\n", marker,
                         segment_length);
            SKIP_SEGLEN(buf, (size_t)segment_length);
        }
        }
    }
    return 0;
}

int decode_header(uint8_t const **buf, struct jpg_image_t *const state) {
    int ret = decode_before_sof(buf, state);
    if (ret != 0) {
        return 1;
    }
    while (1) {
        uint8_t const upper = READ_BYTE(buf);
        if (upper == 0xff) {
            uint8_t const lower = READ_BYTE(buf);
            if (lower == 0xd9)
                break;
        }
    };
    return 0;
}
