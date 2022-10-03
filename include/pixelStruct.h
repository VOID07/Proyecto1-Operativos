#ifndef PIXEL_STRUCT_H
#define PIXEL_STRUCT_H

#include <stdint.h>
#include <time.h>

struct pixel {
    uint8_t pixel_value;
    uint8_t encoded_pixel_value;
    int i; // Lugar en la estructura que fue introducido 
    int j;
    struct tm date;

};
#endif