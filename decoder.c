#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

#include "include/memoryWraper.h"
#include "include/pixelStruct.h"

const char *bit_rep[16] = {
    [0] = "0000",
    [1] = "0001",
    [2] = "0010",
    [3] = "0011",
    [4] = "0100",
    [5] = "0101",
    [6] = "0110",
    [7] = "0111",
    [8] = "1000",
    [9] = "1001",
    [10] = "1010",
    [11] = "1011",
    [12] = "1100",
    [13] = "1101",
    [14] = "1110",
    [15] = "1111",
};

// Estructura usada para cada pixel
// struct pixel
// {
//     uint8_t pixel_value;
//     uint8_t encoded_pixel_value;
//     int i; // Lugar en la estructura que fue introducido
//     int j;
//     struct tm date;
// };

// Función que se encarga de asignar los datos respectivos de cada pixel
struct pixel fill_pixel_data(unsigned char *image_data, int width, int channels, int i, int j, int key)
{

    struct pixel pixeln;

    unsigned bytePerPixel = channels; // i(ancho)  //j(alto hacia abajo)
    unsigned char *pixelOffset = image_data + (i + width * j) * bytePerPixel;

    pixeln.pixel_value = pixelOffset[0];
    pixeln.encoded_pixel_value = pixeln.pixel_value ^ key;
    pixeln.i = i;
    pixeln.j = j;
    time_t t = time(NULL);
    struct tm tiempoLocal = *localtime(&t);
    pixeln.date = tiempoLocal;

    return pixeln;
}

// Función que le da formato a una fecha
int get_date(struct tm tiempoLocal)
{
    // Tiempo actual
    // time_t t = time(NULL);
    // struct tm tiempoLocal = *localtime(&t);
    // El lugar en donde se pondrá la fecha y hora formateadas
    char fechaHora[70];
    // El formato
    char *formato = "%Y-%m-%d %H:%M:%S";
    // Intentar formatear
    int bytesEscritos =
        strftime(fechaHora, sizeof fechaHora, formato, &tiempoLocal);
    if (bytesEscritos != 0)
    {
        // Si no hay error, los bytesEscritos no son 0
        printf("Fecha y hora de guardado: %s \n", fechaHora);
    }
    else
    {
        printf("Error formateando fecha");
    }

    return 0;
}

/*Cuando se ejecuta este proceso debe de recibir 2 parametros, que corresponden a los siguientes
datos: modo de ejecucion, y la clave.*/
int main(int argc, char *argv[])
{
    // valores de prueba
    const int width = 100; // deberíamos pasarle de alguna forma estos datos desde el encodificador
    const int height = 100;
#define CHANNEL_NUM 1

    uint8_t key = atoi(argv[1]);

    // int stbi_write_jpg(char const *filename, int w, int h, int comp, const void *data, int quality);

    // stbi_write_jpg(filename->valuestring, width, height, channels, image, 100);

    //--------------------------------------------------------------------

    // uint8_t* pixels = new uint8_t[width * height * CHANNEL_NUM];

    size_t img_size = width * height * CHANNEL_NUM;

    unsigned char *pixels_img = malloc(img_size);
    if (pixels_img == NULL)
    {
        printf("Unable to allocate memory for the gray image.\n");
        exit(1);
    }

    // uint8_t* pixels = malloc(width * height * CHANNEL_NUM *sizeof(uint8_t));

    int index = 0;
    uint8_t pixel_decoded;
    // valor de prueba
    pixel_decoded = 128;
    for (int j = height - 1; j >= 0; --j)
    {
        for (int i = 0; i < width; ++i)
        {

            /*uint8_t pixel_decoded = pixeln.encoded_pixel_value^key; /*Aquí se debe obtener los datos de la estructura guardada en memoria compartida
                                                                      y se decodifica el valor del pixel para almacenarlo en el nuevo vector con la data*/

            pixels_img[index++] = pixel_decoded;

            // Datos del pixel extraído de memoria compartida
            printf("Pixel value: %s%s, Encoded pixel value: %s%s, índice: %d, índice %d \n", bit_rep[pixeln.pixel_value >> 4], bit_rep[pixeln.pixel_value & 0x0F], bit_rep[pixeln.encoded_pixel_value >> 4], bit_rep[pixeln.encoded_pixel_value & 0x0F], pixeln.i, pixeln.j);
            // Se muestra la fecha formateada para verificar que se esté guardando correctamente en el struct
            get_date(pixeln.date);
        }
    }

    // You have to use 3 comp for complete jpg file. If not, the image will be grayscale or nothing.
    stbi_write_jpg("image.jpg", width, height, 1, pixels_img, 100);

    free(pixels_img);

    return 0;
}

// Para compilarlo: gcc -std=c17 -Wall -pedantic decoder.c -o decoder -lm
// Para ejecutarlo: ./decoder 170
