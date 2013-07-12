/* 
 * File:   type.h
 * Author: sandi
 *
 * Created on 10 Juli 2013, 13:51
 */

#ifndef _TYPE_H
#define	_TYPE_H

typedef struct {

    int imgWidth;
    int imgHeight;    
    unsigned char *data;

} TEXTUREIMAGE;

typedef struct {

    unsigned short bfType;
    unsigned long bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned long bfOffBits;

} BMPFILEHEADER;

typedef struct {

    unsigned long   biSize;
    long            biWidth;
    long            biHeight;
    unsigned short  biPlanes;
    unsigned short  biBitCount;
    unsigned long   biCompression;
    unsigned long   biSizeImage;
    long            biXPelsPerMeter;
    long            biYPelsPerMeter;
    unsigned long   biClrUsed;
    unsigned long   biClrImportant;

} BMPINFOHEADER;

typedef struct {

    float ambient[4];
    float diffuse[4];
    float specular[4];
    float shininess;

} MATERIAL;

typedef struct {

    float lightAmbient[4];
    float lightDiffuse[4];
    float lightSpecular[4];
    float lightPosition[4];

} LIGHT;

#endif	/* _TYPE_H */

