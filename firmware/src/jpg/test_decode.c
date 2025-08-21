#include "decode.h"
#include "header.h"

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t get_file_size(FILE *f) {
    fseek(f, 0, SEEK_END);
    size_t file_size = ftell(f);
    fseek(f, 0, SEEK_SET);
    return file_size;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <jpg file path>\n", argv[0]);
        return 1;
    }
    char *filename = argv[1];
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        printf("Failed to open file: %s\n", strerror(errno));
        return 2;
    }

    size_t file_size = get_file_size(f);
    uint8_t *buf = (uint8_t *)malloc(file_size);
    if (buf == NULL) {
        printf("Failed to allocate memory: %s\n", strerror(errno));
        return 3;
    }

    uint8_t *buf_start = buf;

    size_t read = fread(buf, 1, file_size, f);
    if (read != file_size) {
        printf("Not all bytes were read.\n");
        return 4;
    }

    struct jpgdec_state_t state = (struct jpgdec_state_t){
        .decode_state = BEFORE_IMAGE_DATA,
        .density_units = 0,
        .density_width = 0,
        .density_height = 0,
    };

    int ret = decode_n_mcu(((uint8_t const **)&buf), 0 /*TODO*/, &state);
    if (ret != 0) {
        printf("Failed to decode: %d\n", ret);
        return 5;
    }

    print_state(&state);

    free(buf_start);
    fclose(f);
    printf("Success\n");
    return 0;
}
