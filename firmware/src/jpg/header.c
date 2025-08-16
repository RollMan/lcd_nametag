#include "header.h"

#include "binread.h"
#include "decode.h"
#include "header/segments.h"

int decode_header(char const *buf, jpgdec_state_t *const state) {
    uint16_t start_of_image = READ_WORD(buf);
    if (start_of_image != START_OF_IMAGE) {
        return 1;
    }
    while (true) {
        const uint16_t marker = READ_WORD(buf);
        const uint16_t segment_length = READ_WORD(buf);
        switch (marker) {
        case APPLICATION_DEFAULT_HEADER:
            break;
        default:
            buf += segment_length;
        }
    }
    return 0;
}
