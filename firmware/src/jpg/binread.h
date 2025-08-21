#ifndef __BINREAD_H__
#define __BINREAD_H__
#include <stddef.h>
#include <stdint.h>

typedef enum {
    START_OF_IMAGE = 0xffd8,
    APPLICATION_DEFAULT_HEADER = 0xffe0,
    QUANTIZATION_TABLE = 0xffdb,
    START_OF_FRAME = 0xffc0,
    DEFINE_HUFFMAN_TABLE = 0xffc4,
    START_OF_SCAN = 0xffda,
    END_OF_IMAGE = 0xffd9,
    COMMENT = 0xfffe,
} marker_mapping;

static const size_t SEGMENT_LENGTH_FIELD_SIZE = 2;

static inline void SKIP_SEGLEN(uint8_t const **p, size_t segment_length) {
    *p += segment_length - SEGMENT_LENGTH_FIELD_SIZE;
}

static inline uint8_t READ_BYTE(uint8_t const **p) { return *(*p)++; }

static inline uint16_t READ_WORD(uint8_t const **p) {
    uint16_t high = *(*p)++;
    uint16_t low = *(*p)++;
    return (high << 8) | low;
}

#endif
