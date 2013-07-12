#ifndef _DRAW_H
#define	_DRAW_H

#include <stdio.h>
#include <GL/glut.h>

/* fungsi untuk menggambar objek dasar bola planet, dibuat oleh hilda */
void gltDrawSphere(GLfloat fRadius, GLint iSlices, GLint iStacks)
{
    //printf("gltDrawSphere - start\n");
    GLfloat drho = (GLfloat)(3.141592653589) / (GLfloat) iStacks;
    GLfloat dtheta = 2.0f * (GLfloat)(3.141592653589) / (GLfloat) iSlices;
    GLfloat ds = 1.0f / (GLfloat) iSlices;
    GLfloat dt = 1.0f / (GLfloat) iStacks;
    GLfloat t = 1.0f;
    GLfloat s = 0.0f;
    GLint i, j;

    for (i = 0; i < iStacks; i++)
    {
        GLfloat rho = (GLfloat)i * drho;
    GLfloat srho = (GLfloat)(sin(rho));
    GLfloat crho = (GLfloat)(cos(rho));
    GLfloat srhodrho = (GLfloat)(sin(rho + drho));
    GLfloat crhodrho = (GLfloat)(cos(rho + drho));

        glBegin(GL_TRIANGLE_STRIP);
        s = 0.0f;
        for ( j = 0; j <= iSlices; j++)
        {
            GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;
            GLfloat stheta = (GLfloat)(-sin(theta));
            GLfloat ctheta = (GLfloat)(cos(theta));

            GLfloat x = stheta * srho;
            GLfloat y = ctheta * srho;
            GLfloat z = crho;

            glTexCoord2f(s, t);
            glNormal3f(x, y, z);
            glVertex3f(x * fRadius, y * fRadius, z * fRadius);

            x = stheta * srhodrho;
            y = ctheta * srhodrho;
            z = crhodrho;
            glTexCoord2f(s, t - dt);

            s += ds;
            glNormal3f(x, y, z);
            glVertex3f(x * fRadius, y * fRadius, z * fRadius);
        }
        glEnd();

        t -= dt;
    }
    //printf("gltDrawSphere - end\n");
}


#endif	/* _DRAW_H */

