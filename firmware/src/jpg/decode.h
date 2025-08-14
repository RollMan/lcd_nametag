/*
 * Enum to represent decoding state.
 * This decoder decodes JPEG by image data section (after start of scan section)
 * at once. Then image data is decoded successively. decode_state_t, therefore,
 * consists of before-image-data and after-image-data.
 */
typedef enum {
    BEFORE_IMAGE_DATA,
    INSIDE_IMAGE_DATA,
    AFTER_IMAGE_DATA
} decode_state_t;

struct jpgdec_state_t {
    decode_state_t decode_state;
};
