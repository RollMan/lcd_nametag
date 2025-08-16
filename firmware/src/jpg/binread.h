#ifndef __BINREAD_H__
#define __BINREAD_H__
#include <stdint.h>

typedef enum {
    START_OF_IMAGE = 0xffd8,
    APPLICATION_DEFAULT_HEADER = 0xffe0,
    QUANTIZATION_TABLE = 0xffdb,
    START_OF_FRAME = 0xffc0,
    DEFINE_HUFFMAN_TABLE = 0xffc4,
    START_OF_SCAN = 0xffda,
    END_OF_IMAGE = 0xffd9,
} marker_mapping;

#define READ_BYTE(p) (*p++)

static inline uint16_t READ_WORD(uint8_t const **p) {
    uint16_t high = *(*p)++;
    uint16_t low = *(*p)++;
    return (high << 8) | low;
}

#endif
