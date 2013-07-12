/* 
 * File:   main.cpp
 * Author: maryana
 *
 * Created on 10 Juli 2013, 13:49
 */

#include <GL/glut.h>
#include <windows.h>
#include <mmsystem.h>
#include <math.h>
#include "type.h"
#include "bmp.h"
#include "mf.h"
#include "draw.h"

#define  DEG_TO_RAD 0.017453

static GLuint texName;
bool   g_bOrbitOn = true;
float  g_fSpeedmodifier = 1.0f;
float  g_fElpasedTime;
double g_dCurrentTime;
double g_dLastTime;

static GLdouble viewer[]= { -sin(10*DEG_TO_RAD), 10*cos(10*DEG_TO_RAD), -25 };
static int year =0 ,day = 0;
float angle=0.0;

TEXTUREIMAGE  earthImg;
TEXTUREIMAGE  sunImg;
TEXTUREIMAGE  moonImg;
TEXTUREIMAGE  venusImg;
TEXTUREIMAGE  spaceImg;
TEXTUREIMAGE  saturnImg;
TEXTUREIMAGE  jupiterImg;
TEXTUREIMAGE  neptuneImg;
TEXTUREIMAGE  uranusImg;
TEXTUREIMAGE  marsImg;
TEXTUREIMAGE  mercuryImg;

#define NUM_TEXTURES    20
GLuint  textureObjects[NUM_TEXTURES];

MATERIAL material[NUM_TEXTURES];

LIGHT light =
{
	{0.0, 0.0, 0.0, 1.0},
	{1.0, 1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0, 1.0},
	{0.0, 0.0, 0.0, 1.0}
};
MATERIAL materialSpace =
{
    {0.4, 0.4, 0.4, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    0.0
};
MATERIAL materialSun =
{
    {100.0, 100.0, 100.0, 20.0},
    {0.8, 0.8, 0.8, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    0.0
};
MATERIAL materialEarth =
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    100.0
};
MATERIAL materialMoon =
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    0.0
};
MATERIAL materialSaturn =
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    100.0
};
MATERIAL materialJupiter =
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    100.0
};
MATERIAL materialNeptune =
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    100.0
};
MATERIAL materialMars =
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    100.0
};
MATERIAL materialMercury =
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    100.0
};
MATERIAL materialUranus =
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    100.0
};

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);

    material[0]=materialSun;
    material[1]=materialEarth ;
    material[2]=materialMoon ;
    material[3]=materialSpace ;
    material[4]=materialSaturn;
    material[5]=materialJupiter;
    material[6]=materialNeptune;
    material[7]=materialUranus;
    material[8]=materialMars;
    material[9]=materialMercury;

    GLfloat light_ambient[]={1.0, 1.0, 1.0, 1.0};
    GLfloat light_diffuse[]={1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[]={1.0, 1.0, 1.0, 1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(int w,int h)
{
    glViewport(0,0,(GLint) w, (GLint) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0,(GLfloat)w/(GLfloat)h,1.0,200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(viewer[0],viewer[1],viewer[2],0,0,0,0,0,1);
}

void ShutdownRC(void)
{
    glDeleteTextures(NUM_TEXTURES, textureObjects);
}

void display(void)
{
    glLoadIdentity();
    gluLookAt(viewer[0],viewer[1],viewer[2],0,0,0,0,0,1);

    g_dCurrentTime = timeGetTime();
    g_fElpasedTime = (float)((g_dCurrentTime - g_dLastTime) * 0.001);
    g_dLastTime    = g_dCurrentTime;

    GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };

    static float fSunSpin    = 0.0f;
    static float fMercurySpin  = 0.0f;
    static float fMercuryOrbit = 0.0f;

    static float fVenusSpin  = 0.0f;
    static float fVenusOrbit = 0.0f;

    static float fEarthSpin  = 0.0f;
    static float fEarthOrbit = 0.0f;

    static float fMoonSpin   = 0.0f;
    static float fMoonOrbit  = 0.0f;

    static float fMarsSpin   = 0.0f;
    static float fMarsOrbit  = 0.0f;

    static float fJupiterSpin   = 0.0f;
    static float fJupiterOrbit  = 0.0f;

    static float fNeptuneSpin   = 0.0f;
    static float fNeptuneOrbit  = 0.0f;

    static float fUranusSpin   = 0.0f;
    static float fUranusOrbit  = 0.0f;

    static float fSaturnSpin   = 0.0f;
    static float fSaturnOrbit  = 0.0f;

    float spaceWidth =18.50;
    float spacedepth =8.0;

    static float MercuryToSun       = -3.0;
    static float VenToSun           = -5.0;
    static float earthToSun         = -7.0;
    static float moonToEarth        = -0.9f;
    static float MarsToSun          = -9.0;
    static float JupiterToSun       = -11.0;
    static float NeptuneToSun       = -14.0;
    static float SaturnToSun        = -12.0;
    static float UranusToSun        = -15.0;

    if( g_bOrbitOn == true )
    {
        fSunSpin -= g_fSpeedmodifier * (g_fElpasedTime * 10.0f);

        fEarthSpin  -= g_fSpeedmodifier * (g_fElpasedTime * 100.0f);
        fEarthOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 20.5f);

        fMoonSpin  -= g_fSpeedmodifier * (g_fElpasedTime * 50.0f);
        fMoonOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 200.0f);

        fVenusSpin -= g_fSpeedmodifier * (g_fElpasedTime * 10.0f);
        fVenusOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 20.8f);

        fSaturnSpin -= g_fSpeedmodifier * (g_fElpasedTime * 10.0f);
        fSaturnOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 20.2f);

        fJupiterSpin -= g_fSpeedmodifier * (g_fElpasedTime * 10.0f);
        fJupiterOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 20.0f);

        fNeptuneSpin -= g_fSpeedmodifier * (g_fElpasedTime * 10.0f);
        fNeptuneOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 19.8f);

        fUranusSpin -= g_fSpeedmodifier * (g_fElpasedTime * 10.0f);
        fUranusOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 19.5f);

        fMarsSpin -= g_fSpeedmodifier * (g_fElpasedTime * 10.0f);
        fMarsOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 19.2f);

        fMercurySpin -= g_fSpeedmodifier * (g_fElpasedTime * 10.0f);
        fMercuryOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 19.0f);
    }

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_MODELVIEW );

    // Set up texture maps
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_SPECULAR,material[3].specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material[3].ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material[3].diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, material[3].shininess);

    glPushMatrix();
        mf(spaceImg,& textureObjects[0]);
        glRotatef(90,1,1.0,0.0);
	gltDrawSphere(40,100,100);
    glPopMatrix();
    glDeleteTextures(1, &textureObjects[0]);


    /********************************** matahari *******************************************/
    glMaterialfv(GL_FRONT, GL_SPECULAR,material[0].specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material[0].ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material[0].diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, material[0].shininess);
    glColor3f(1,1,1);

    glPushMatrix();
        glRotatef(10,1,0.0,0.0);
	glRotatef(fSunSpin,0.0,1.0,0.0);
	glRotatef(90,1,0.0,0.0);
        mf(sunImg,& textureObjects[0]);
   	gltDrawSphere(2,200,200);
    glPopMatrix();
    glDeleteTextures(1, &textureObjects[0]);
    /********************************** akhir matahari *******************************************/


    /************************ bumi *******************************/
    glMaterialfv(GL_FRONT, GL_SPECULAR,material[1].specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material[1].ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material[1].diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, material[1].shininess);

    glPushMatrix();
	glRotatef(fEarthOrbit,0.0,1.0,0.0);
	glTranslatef(0.0,0.0,earthToSun);
	glRotatef(fEarthSpin,0.0,1.0,0.0);
	glRotatef(10,0,0.0,1.0);
	glRotatef(90,1,0.0,0.0);

        mf(earthImg,& textureObjects[0]);
   	gltDrawSphere(0.6,100,100);
    glPopMatrix();
    /************************ akhir bumi *******************************/


    /************************ orbit bumi *******************************/
    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(earthToSun*sin(DEG_TO_RAD*angle),0,earthToSun*cos(DEG_TO_RAD*angle));
    glEnd();
    glDeleteTextures(1, &textureObjects[0]);
    /************************ akhir orbit bumi *******************************/


    /************************ bulan *******************************/
    glPushMatrix();
        glRotatef( fEarthOrbit, 0.0f, 1.0f, 0.0f );
        glTranslatef( 0.0f, 0.0f, earthToSun);
        glRotatef( fMoonOrbit, 0.0f, 1.0f, 0.0f );
        glTranslatef( 0.0f, 0.0f, moonToEarth );
        glRotatef( fMoonSpin, 0.0f, 1.0f, 0.0f );
        glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	glRotatef(90,1,0.0,0.0);
        mf(moonImg,& textureObjects[0]);
   	gltDrawSphere(0.2,50,20);
    glPopMatrix();
    glDeleteTextures(1, &textureObjects[0]);
    /************************ akhir bulan *******************************/


    /************************ venus *******************************/
    glColor3f(192,122,24);
    glPushMatrix();
	glRotatef(fVenusOrbit,0.0,1.0,0.0);
	glTranslatef(0.0,0.0,VenToSun);
	glRotatef(fVenusSpin,0.0,1.0,0.0);
	glRotatef(90,1,0.0,0.0);
	mf(venusImg,& textureObjects[0]);
   	gltDrawSphere(0.5,150,200);
    glPopMatrix();
    /************************ akhir venus *******************************/


    /************************ orbit venus *******************************/
    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(VenToSun*sin(DEG_TO_RAD*angle),0,VenToSun*cos(DEG_TO_RAD*angle));
    glEnd();
    glDeleteTextures(1, &textureObjects[0]);
    /************************ akhir orbit venus *******************************/


    /************************ saturnus *******************************/
    glColor3f(192,122,24);
    glPushMatrix();
	glRotatef(fSaturnOrbit,0.0,1.0,0.0);
	glTranslatef(0.0,0.0,SaturnToSun);
	glRotatef(fSaturnSpin,0.0,1.0,0.0);
	glRotatef(90,1,0.0,0.0);
	mf(saturnImg, &textureObjects[0]);
   	gltDrawSphere(0.5,150,200);
    glPopMatrix();
    /************************ akhir saturnus *******************************/


    /************************ orbit saturnus *******************************/
    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(SaturnToSun*sin(DEG_TO_RAD*angle),0,SaturnToSun*cos(DEG_TO_RAD*angle));
    glEnd();
    glDeleteTextures(1, &textureObjects[0]);
    /************************ akhir orbit saturnus *******************************/


    /************************ yupiter *******************************/
    glColor3f(192,122,24);
    glPushMatrix();
	glRotatef(fJupiterOrbit,0.0,1.0,0.0);
	glTranslatef(0.0,0.0,JupiterToSun);
	glRotatef(fJupiterSpin,0.0,1.0,0.0);
	glRotatef(90,1,0.0,0.0);
	mf(jupiterImg, &textureObjects[0]);
   	gltDrawSphere(0.5,150,200);
    glPopMatrix();
    /************************ akhir yupiter *******************************/


    /************************ orbit yupiter *******************************/
    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(JupiterToSun*sin(DEG_TO_RAD*angle),0,JupiterToSun*cos(DEG_TO_RAD*angle));
    glEnd();
    glDeleteTextures(1, &textureObjects[0]);
    /************************ akhir orbit yupiter *******************************/


    /************************ neptunus *******************************/
    glColor3f(192,122,24);
    glPushMatrix();
	glRotatef(fNeptuneOrbit,0.0,1.0,0.0);
	glTranslatef(0.0,0.0,NeptuneToSun);
	glRotatef(fNeptuneSpin,0.0,1.0,0.0);
	glRotatef(90,1,0.0,0.0);
	mf(neptuneImg, &textureObjects[0]);
   	gltDrawSphere(0.5,150,200);
    glPopMatrix();
    /************************ akhir neptunus *******************************/


    /************************ orbit neptunus *******************************/
    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(NeptuneToSun*sin(DEG_TO_RAD*angle),0,NeptuneToSun*cos(DEG_TO_RAD*angle));
    glEnd();
    glDeleteTextures(1, &textureObjects[0]);
    /************************ akhir orbit neptunus *******************************/


    /************************ uranus *******************************/
    glColor3f(192,122,24);
    glPushMatrix();
	glRotatef(fUranusOrbit,0.0,1.0,0.0);
	glTranslatef(0.0,0.0,UranusToSun);
	glRotatef(fUranusSpin,0.0,1.0,0.0);
	glRotatef(90,1,0.0,0.0);
	mf(uranusImg,& textureObjects[0]);
   	gltDrawSphere(0.5,150,200);
    glPopMatrix();
    /************************ akhir uranus *******************************/

    /************************ orbit uranus *******************************/
    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(UranusToSun*sin(DEG_TO_RAD*angle),0,UranusToSun*cos(DEG_TO_RAD*angle));
    glEnd();
    glDeleteTextures(1, &textureObjects[0]);
    /************************ akhir orbit uranus *******************************/


    /************************ mars *******************************/
    glColor3f(192,122,24);
    glPushMatrix();
	glRotatef(fMarsOrbit,0.0,1.0,0.0);
	glTranslatef(0.0,0.0,MarsToSun);
	glRotatef(fMarsSpin,0.0,1.0,0.0);
	glRotatef(90,1,0.0,0.0);
	mf(marsImg,& textureObjects[0]);
   	gltDrawSphere(0.5,150,200);
    glPopMatrix();
    /************************ akhir mars *******************************/


    /************************ orbit mars *******************************/
    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(MarsToSun*sin(DEG_TO_RAD*angle),0,MarsToSun*cos(DEG_TO_RAD*angle));
    glEnd();
    glDeleteTextures(1, &textureObjects[0]);
    /************************ akhir orbit mars *******************************/


    /************************ merkurius *******************************/
    glColor3f(192,122,24);
    glPushMatrix();
	glRotatef(fMercuryOrbit,0.0,1.0,0.0);
	glTranslatef(0.0,0.0,MercuryToSun);
	glRotatef(fMercurySpin,0.0,1.0,0.0);
	glRotatef(90,1,0.0,0.0);
	mf(mercuryImg,& textureObjects[0]);
   	gltDrawSphere(0.5,150,200);
    glPopMatrix();
    /************************ akhir merkurius *******************************/


    /************************ orbit merkurius *******************************/
    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(MercuryToSun*sin(DEG_TO_RAD*angle),0,MercuryToSun*cos(DEG_TO_RAD*angle));
    glEnd();
    glDeleteTextures(1, &textureObjects[0]);
    /************************ akhir orbit merkurius *******************************/


    glutSwapBuffers();
    glFlush();
}

void keyboard(unsigned char key ,int x,int y)
{
    switch(key) {
	case'=':
		++g_fSpeedmodifier;
		glutPostRedisplay();
		break;

	case ' ':
		g_bOrbitOn = !g_bOrbitOn;
		glutPostRedisplay();
		break;

	case'-':
		--g_fSpeedmodifier;
		glutPostRedisplay();
		break;

	case'w':
		viewer[0]+= 0.1;
		break;

	case'e':
		viewer[0]-= 0.1;
		break;

	case's':
		viewer[1]+=0.1;
		break;

	case'd':
		viewer[1]-=0.1;
		break;

	case'x':
		viewer[2]+=0.1;
		break;

	case'c':
		viewer[2]-=0.1;
		break;

	default:
		break;

	}
	display();
}

void mouse(int btn, int state, int x, int y)
{
    static  int axis=0;
    if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        axis++;
        axis=axis%5;
    }
    if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        axis--;
	if(axis==-1) axis=4;
    }
    switch(axis) {
        case 0:
            viewer[0] = -sin(10*DEG_TO_RAD);
            viewer[1] = cos(10*DEG_TO_RAD);
            viewer[2] = -15;
            break;

        case 1:
            viewer[0] = 1;
            viewer[1] = 20;
            viewer[2] = 1;
            break;

        case 2:
            viewer[0] = -sin(10*DEG_TO_RAD);
            viewer[1] = 10*cos(10*DEG_TO_RAD);
            viewer[2] = -13;
            break;

	case 3:
            viewer[0] = -5;
            viewer[1] = 15;
            viewer[2] = -15;
            break;


	case 4:
            viewer[0] = -sin(10*DEG_TO_RAD);
            viewer[1] = 10*cos(10*DEG_TO_RAD);
            viewer[2] = -25;
            break;

	default:
	break;
    }
    display();
}

int main(int argc, char**argv)
{
    GLsizei width, height;
    width = glutGet(GLUT_SCREEN_WIDTH);
    height= glutGet(GLUT_SCREEN_HEIGHT);

    LoadBmp("image//sun.bmp"    , &sunImg);
    LoadBmp("image//earth.bmp"  , &earthImg);
    LoadBmp("image//moon.bmp"   , &moonImg);
    LoadBmp("image//venus.bmp"  , &venusImg);
    LoadBmp("image//sky.bmp"    , &spaceImg);
    LoadBmp("image//saturn.bmp"    , &saturnImg);
    LoadBmp("image//jupiter.bmp"    , &jupiterImg);
    LoadBmp("image//neptune.bmp"    , &neptuneImg);
    LoadBmp("image//uranus.bmp"    , &uranusImg);
    LoadBmp("image//mars.bmp"    , &marsImg);
    LoadBmp("image//mercury.bmp"    , &mercuryImg);

    /*******************************************************/

    glutInit(&argc,argv);
    glutInitWindowPosition( width / 4, height / 4 );
    glutInitWindowSize( width / 2, height / 2 );
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutCreateWindow("Tata Surya - IF17K Kelompok 3");
    init();

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();
    ShutdownRC();
    return 0;
}

