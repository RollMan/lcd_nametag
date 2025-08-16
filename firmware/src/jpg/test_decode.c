#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "header.h"

int main(int argc, char** argv){
    if (argc != 2){
        printf("Usage: %s <jpg file path>\n", argv[0]);
        return 1;
    }
    char* filename = argv[1];
    FILE* f = fopen(filename, "rb");
    if (f == NULL){
        printf("Failed to open file: %s\n", strerror(errno));
        return 2;
    }
    return 0;
}
