
#include <GL/glut.h>
#include <math.h>

#include "helpers.h"

#define PI 3.14159265
GLuint tunnelTexture;

unsigned char *imagedata;
int height, width;

void init()
{
	tunnelTexture = loadTexture("images/illusion.jpg");
  // Place one-time initialization code here
}

void display()
{
  // This function is called whenever it is time to render
  //  a new frame; due to the idle()-function below, this
  //  function will get called several times per second

  // Clear framebuffer & zbuffer
  glClearColor(0.3, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90, 1, 0.01, 100);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
   glEnable(GL_TEXTURE_2D);
  glLoadMatrixd(getObjectMatrix());
  // Enable Gouraud shading
  glShadeModel(GL_SMOOTH);

  // Draw polygon
  //glEnable(GL_CULL_FACE);
  //glCullFace(GL_BACK);

float depth = -5;
int z = 1;
int zstep = 1;
float ztexstep = 0.01;
//float hyp = 5;
float textint = 0;
glBindTexture(GL_TEXTURE_2D, tunnelTexture);


float ztexphase = 0;
 //glRotatef(getElapsedTime()*5, 0, 0, 1);
for (;z <= 100; z++) {

  int i = 1;
  for(;i <= 360; i++) {
	//printf("fiskapa %d - ", z);
	//printf("%d", i);
	//printf("\n");
	float hyp =  5 + ((int)imagedata[(z*height + i)*3]) / 50.0;
	//printf("%d\n", height);

	float x = cos(i*PI/180) * hyp;
	float y = sin(i*PI/180) * hyp;
	glNormal3f(0, 1, 0);
	float xplusone = cos((i+1)*PI/180) * hyp;
	float yplusone = sin((i+1)*PI/180) * hyp;
  	glBegin(GL_POLYGON);
        glTexCoord2f(ztexphase, textint);
	glVertex3f(x, y, -z);

        glTexCoord2f(ztexphase+ztexstep, textint);	
	glVertex3f(x, y, -(z + zstep));

        glTexCoord2f(ztexphase+ztexstep, textint+10/360);
	glVertex3f(xplusone, yplusone, -(z + zstep));

        glTexCoord2f(ztexphase, textint+10/360); 	
	glVertex3f(xplusone, yplusone, -z);
  	glEnd();
	textint = (textint+10/360);
	ztexphase += ztexstep;
  }
}
/*
glBegin(GL_POLYGON);
  glColor3f(1, 0, 0);
  glVertex3f(-4.5, 0.5, 0.0);
  glColor3f(0, 1, 0);
  glVertex3f(-5,0.0, 0.0);
  glColor3f(0, 0, 1);
  glVertex3f(-5,0.0, -10.0);
  glColor3f(1, 0, 1);  
  glVertex3f(-4.5, 0.5, -10.0);

  glColor3f(0,0.4,0.7);
  glVertex3f(-4.0,1.0,0.0);
  glColor3f(0.6,0.3,0.0);
  glVertex3f(-3.5,1.5,0.0);
  glColor3f(0.2,1.0,0.0);
  glVertex3f(-3.5,1.50,-10.0);
  glColor3f(1.0,0.4,0.4);
  glVertex3f(-4,1.0,-10.0);

  glEnd();
/*
 
  glBegin(GL_POLYGON);
  glColor3f(0,0.9,0.3);
  glVertex3f(0.1,0.1,-0.2);
  glColor3f(0.2,0.4,0.7);
  glVertex3f(0.1,0.1,0.0);
  glColor3f(0.5,0,0.7);
  glVertex3f(0.1,-0.1,0.0);
  glColor3f(0,0.3,0.8);
  glVertex3f(0.1,-0.1,-0.2);

  glColor3f(1,0.2,0.7);
  glVertex3f(0.1,0.1,-0.2);
  glColor3f(1,0.5,0.3);
  glVertex3f(0.1,-0.1,-0.2);
  glColor3f(0,0.9,0.7);
  glVertex3f(-0.1,-0.1,-0.2);
  glColor3f(0,0.1,0.7);
  glVertex3f(-0.1,0.1,-0.2);

  glEnd();

 
  glBegin(GL_POLYGON);
  glColor3f(0.2,0.8,0.7);
  glVertex3f(-0.1,-0.1,0.0);
  glColor3f(0.6,0.1,0.2);
  glVertex3f(-0.1,-0.1,-0.2);
  glColor3f(1,0.4,0.2);
  glVertex3f(0.1,-0.1,-0.2);
  glColor3f(0.1,0.4,1);
  glVertex3f(0.1,-0.1,0.0);
*/

/*
  glBegin(GL_POLYGON);

  //framsida
  glColor3f(1, 0, 0);
  glVertex3f(-0.1, 0.1, 0.0);
  glColor3f(0, 1, 0);
  glVertex3f(-0.1,-0.1, 0.0);
  glColor3f(0, 0, 1);
  glVertex3f(0.1,-0.1, 0.0);
  glColor3f(1, 0, 1);  
  glVertex3f(0.1, 0.1, 0.0);

  //TOP
  glColor3f(0, 1, 1);
  glVertex3f(-0.1, 0.1, 0.0);
  glColor3f(1, 1, 0);
  glVertex3f(0.1, 0.1, 0.0);
  glColor3f(1, 1, 1);
  glVertex3f(0.1,0.1,-0.2);
  glColor3f(0.3, 0.6, 1);
  glVertex3f(-0.1,0.1,-0.2);

  //left
  glColor3f(0,0.4,0.7);
  glVertex3f(-0.1,0.1,0.0);
  glColor3f(0.6,0.3,0.0);
  glVertex3f(-0.1,0.1,-0.2);
  glColor3f(0.2,1.0,0.0);
  glVertex3f(-0.1,-0.1,-0.2);
  glColor3f(1.0,0.4,0.4);
  glVertex3f(-0.1,-0.1,0.0);

  glEnd();
  glBegin(GL_POLYGON);
  //right
  glColor3f(0,0.9,0.3);
  glVertex3f(0.1,0.1,-0.2);
  glColor3f(0.2,0.4,0.7);
  glVertex3f(0.1,0.1,0.0);
  glColor3f(0.5,0,0.7);
  glVertex3f(0.1,-0.1,0.0);
  glColor3f(0,0.3,0.8);
  glVertex3f(0.1,-0.1,-0.2);

  //background
  glColor3f(1,0.2,0.7);
  glVertex3f(0.1,0.1,-0.2);
  glColor3f(1,0.5,0.3);
  glVertex3f(0.1,-0.1,-0.2);
  glColor3f(0,0.9,0.7);
  glVertex3f(-0.1,-0.1,-0.2);
  glColor3f(0,0.1,0.7);
  glVertex3f(-0.1,0.1,-0.2);

  glEnd();
  glBegin(GL_POLYGON);
  //bottom
  glColor3f(0.2,0.8,0.7);
  glVertex3f(-0.1,-0.1,0.0);
  glColor3f(0.6,0.1,0.2);
  glVertex3f(-0.1,-0.1,-0.2);
  glColor3f(1,0.4,0.2);
  glVertex3f(0.1,-0.1,-0.2);
  glColor3f(0.1,0.4,1);
  glVertex3f(0.1,-0.1,0.0);





  glEnd();
*/


  // Swap front- and backbuffers
  glutSwapBuffers();
}

void load() {
  printf("%s", "yeah");
  imagedata = readppm("../lab4/heightmaps/fft-terrain-360-bred.ppm", &height, &width);
  printf("%d", height);
}

void idle()
{
  // This function is called whenever the computer is idle

  // As soon as the machine is idle, ask GLUT to trigger rendering of a new
  // frame
  glutPostRedisplay();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);

  // Configure GLUT:
  //  - framebuffer with RGB + Alpha values per pixel
  //  - Z-buffer
  //  - two sets of above mentioned buffers, so that
  //    doublebuffering is possible
  //
  // Initial window size 800x800
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(800, 800);
  glutCreateWindow("OpenGL test");

  initHelperLibrary();
  init();
  load();

  // Register our display- and idle-functions with GLUT
  glutDisplayFunc(display);
  glutIdleFunc(idle);

  // Enter GLUT's main loop; this function will never return
  glutMainLoop();

  return 0;
}
