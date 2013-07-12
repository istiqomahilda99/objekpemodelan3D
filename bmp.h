#ifndef _BMP_H
#define	_BMP_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include "type.h"
#include "bmp.h"

/*
 * procedure untuk meload file BMP
 * akan diimplementasikan oleh sandi
 */
void LoadBmp(char *filename, TEXTUREIMAGE *image)
{
    FILE *file; // file bmp yang akan diload
    unsigned long size; // ukuran image dalam bytes
    unsigned long i; // standard counter
    unsigned short int plane; // number of planes in image

    unsigned short int bpp; // jumlah bits per pixel
    char temp; // temporary color storage for var warna sementara untuk memastikan filenya ada

        if ((file = fopen(filename, "rb")) == NULL) {
            printf("File Not Found : %s\n", filename);
            return;
        }
    // mencari file header bmp
    fseek(file, 18, SEEK_CUR);
    // read the width
    
    if ((i = fread(&image->imgWidth, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return;
    }

    // membaca nilai height
    if ((i = fread(&image->imgHeight, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return;
    }
    //printf("Height of %s: %lu\n", filename, image->sizeY)
    //menghitung ukuran image(asumsi 24 bits or 3 bytes per pixel)

    size = image->imgWidth * image->imgHeight * 3;
    // read the planes
    if ((fread(&plane, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return;
    }
    if (plane != 1) {
        printf("Planes from %s is not 1: %u\n", filename, plane);
        return;
    }
    // read the bitsperpixel
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return;
    }
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return;
    }
    // seek past the rest of the bitmap header.
    fseek(file, 24, SEEK_CUR);
    // read the data.
    image->data = (unsigned char *) malloc(size);
    if (image->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return;
    }
    if ((i = fread(image->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return;
        
    }
    for (i = 0; i < size; i += 3) { // membalikan semuan nilai warna (gbr - > rgb)
        temp = image->data[i];
        image->data[i] = image->data[i + 2];
        image->data[i + 2] = temp;
    }
        fclose(file);
}

#endif	/* _BMP_H */

