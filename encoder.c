#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"


const char *bit_rep[16] = {
    [ 0] = "0000", [ 1] = "0001", [ 2] = "0010", [ 3] = "0011",
    [ 4] = "0100", [ 5] = "0101", [ 6] = "0110", [ 7] = "0111",
    [ 8] = "1000", [ 9] = "1001", [10] = "1010", [11] = "1011",
    [12] = "1100", [13] = "1101", [14] = "1110", [15] = "1111",
};

// Declaración de la estructura para cada pixel 
struct pixel {
    uint8_t pixel_value;
    uint8_t encoded_pixel_value;
    int i; // Lugar en la estructura que fue introducido 
    int j;
    struct tm date;

};


// Función que se encarga de asignar los datos respectivos de cada pixel
struct pixel fill_pixel_data (unsigned char *image_data, int width, int channels, int i, int j, int key)
{

    struct pixel pixeln;

    unsigned bytePerPixel = channels;   //i(ancho)  //j(alto hacia abajo)
    unsigned char* pixelOffset = image_data + (i + width * j) * bytePerPixel;

    pixeln.pixel_value = pixelOffset[0];
    pixeln.encoded_pixel_value = pixeln.pixel_value^key;
    pixeln.i=i;
    pixeln.j=j;
    time_t t = time(NULL);
    struct tm tiempoLocal = *localtime(&t);
    pixeln.date = tiempoLocal;


    return pixeln;

}

//Función que le da formato a una fecha 
 int get_date(struct tm tiempoLocal) {
    // Tiempo actual
    //time_t t = time(NULL);
    //struct tm tiempoLocal = *localtime(&t);
    // El lugar en donde se pondrá la fecha y hora formateadas
    char fechaHora[70];
    // El formato
    char *formato = "%Y-%m-%d %H:%M:%S";
    // Intentar formatear
    int bytesEscritos =
        strftime(fechaHora, sizeof fechaHora, formato, &tiempoLocal);
    if (bytesEscritos != 0) {
        // Si no hay error, los bytesEscritos no son 0
        printf("Fecha y hora de guardado: %s \n", fechaHora);
    } else {
        printf("Error formateando fecha");
    }

    return 0;

}

/*Cuando se ejecuta este proceso debe de recibir 4 parametros, que corresponden a los siguientes
datos: nombre de imagen, cantidad de pixeles en el chunk, modo de ejecucion, y la clave.*/
int main(int argc, char *argv[]){

    //Con la cantidad de pixeles se reserva el espacio en la memoria compartida
    //modo de ejecución ya no debería aplicar

    int width, height, channels;
    unsigned char *image_data = stbi_load(argv[1], &width,&height,&channels,0);
    struct pixel pixeln;

    int num_pixels = strtol(argv[2], NULL, 10);
    uint8_t key = atoi(argv[3]);

    printf("Image name: %s, Number of pixels in the chunk: %d, Key value: %d \n",argv[1], num_pixels, key);
    
    if(image_data==NULL){
        printf("Error in loading the image\n");
        exit(1);
    }

    printf("Load image with a width of %dpx,a height of %dpx and %d channels\n", width,height,channels);

    int response;

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {

            pixeln = fill_pixel_data(image_data, width, channels, i, j, key);

            printf("Pixel value: %s%s, Encoded pixel value: %s%s, Date: \n", bit_rep[pixeln.pixel_value >> 4],bit_rep[pixeln.pixel_value & 0x0F], bit_rep[pixeln.encoded_pixel_value >> 4],bit_rep[pixeln.encoded_pixel_value & 0x0F]);
            //Se muestra la fecha formateada para verificar que se esté guardando correctamente en el struct
            get_date(pixeln.date);
   
            printf("continuar? 1=si ó 0=no: ");
            scanf("%d", &response);
            

            if (response == 0)
            {
                printf("fin de la ejecución\n");
                exit(1);
            }
            
        }
        
    }
    

    stbi_image_free(image_data);
}

//Para compilarlo: gcc -std=c17 -Wall -pedantic encoder.c -o encoder -lm
//Para ejecutarlo: ./encoder cameraman.jpg 5000 170
