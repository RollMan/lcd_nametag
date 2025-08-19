#include "header.h"

#include "binread.h"
#include "decode.h"
#include "header/segments.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int decode_before_sof(uint8_t const **buf, struct jpgdec_state_t *const state) {
    uint16_t start_of_image = READ_WORD(buf);
    if (start_of_image != START_OF_IMAGE) {
        return 1;
    }
    uint8_t const *const orig = *buf;
    while (1) {
        printf("==\n%d\n", *buf - orig);
        const uint16_t marker = READ_WORD(buf);
        printf("%d\n", *buf - orig);
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
            const uint16_t segment_length = READ_WORD(buf) - 2;
            char *str = (char *)malloc(sizeof(char) * segment_length + 1);
            str[segment_length + 1] = '\0';
            for (int i = 0; i < segment_length; i++) {
                str[i] = READ_BYTE(*buf);
            }
            printf("COM: %s\n", str);
            free(str);
        } break;
        case END_OF_IMAGE:
            // Unexpected END_OF_IMAGE.
            return -1;
        default: {
            const uint16_t segment_length = READ_WORD(buf);
            printf("marker: %x, seglen: %d\n", marker, segment_length);
            *buf += segment_length - 2;
        }
        }
    }
    return 0;
}

int decode_header(uint8_t const **buf, struct jpgdec_state_t *const state) {
    int ret = decode_before_sof(buf, state);
    if (ret != 0) {
        return 1;
    }
    while (1) {
        uint8_t const upper = READ_BYTE(*buf);
        if (upper == 0xff) {
            uint8_t const lower = READ_BYTE(*buf);
            if (lower == 0xd9)
                break;
        }
    };
    return 0;
}
