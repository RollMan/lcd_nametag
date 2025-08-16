#include "header.h"

#include "binread.h"
#include "decode.h"
#include "header/segments.h"

#include <stdint.h>
#include <stdio.h>

int decode_header(uint8_t const *buf, struct jpgdec_state_t *const state) {
    uint16_t start_of_image = READ_WORD(&buf);
    if (start_of_image != START_OF_IMAGE) {
        return 1;
    }
    while (1) {
        const uint16_t marker = READ_WORD(&buf);
        switch (marker) {
        case APPLICATION_DEFAULT_HEADER:
            int ret = decode_application_default_header(&buf, state);
            if (ret != 0) {
                return ret;
            }
            break;
        case END_OF_IMAGE:
            return 0;
            break;
        default:
            const uint16_t segment_length = READ_WORD(&buf);
            printf("%d\n", segment_length);
            buf += segment_length - 2;
        }
    }
    return 0;
}
