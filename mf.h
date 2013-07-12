/* 
 * File:   mf.h
 * Author: maryana
 *
 * Created on 10 Juli 2013, 13:56
 */

#ifndef _MF_H
#define	_MF_H

#include <GL/glut.h>
#include "type.h"
#include "mf.h"

/* proc untuk melakukan binding image bmp kedalam object */
void mf(TEXTUREIMAGE textureImg, GLuint * texName)
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1,texName);
    glBindTexture(GL_TEXTURE_2D , *texName);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureImg.imgWidth,textureImg.imgHeight, 0,
        GL_RGB, GL_UNSIGNED_BYTE, textureImg.data);
}


#endif	/* _MF_H */

