
#include <GL/glut.h>
#include <math.h>

#include "helpers.h"
typedef struct cube // A Structure To Hold A Single Cube
{
	float x;
	float y;
	float z;
	float rotationPHI;
	float rotationTHETA;
	float rotationALPHA;
// indicates the bottomleftfront corner of the cube, with size:
	float size;
}
CUBE;

CUBE cubes[40];

void init()
{
int i = 0;
int directionX = 1;
int directionY = 1;
for(; i< 40; i++) {
int length = i+1;
if(i>9) {
length = i-9;
directionX = -1;
}
if (i>19) {
length = i-19;
directionY = -1;
}
if (i >29) {
length = i-29;
directionX = 1;
}
cubes[i].x = length*directionX;
cubes[i].y = length*directionY;
cubes[i].z = 0;
cubes[i].rotationPHI = 0;
cubes[i].rotationTHETA = 0;
cubes[i].rotationALPHA = 0;
cubes[i].size = 0.2; 

}
 // Place one-time initialization code here
}


void drawCubes()
{
  glBegin(GL_POLYGON);
  int i = 0;
  for (;i<40; i++) {
  float size = cubes[i].size;
  float x = cubes[i].x;
  float y = cubes[i].y;
  //framsida
  glNormal3f(0,0,1);
  glVertex3f(x-size, y+size, 0.0);
  glVertex3f(x-size,y-size, 0.0);
  glVertex3f(x+size,y-size, 0.0);
  glVertex3f(x+size, y+size, 0.0);

  glEnd();
  glBegin(GL_POLYGON);
  //TOP
  glNormal3f(0, 1, 0);
  glVertex3f(x-size, y+size, 0.0);
  glVertex3f(x+size, y+size, 0.0);
  glVertex3f(x+size,y+size,-size*2);
  glVertex3f(x-size,y+size,-size*2);

  glEnd();
  glBegin(GL_POLYGON);
  //left
  glNormal3f(-1, 0, 0);
  glVertex3f(x-size,y+size,0.0);
  glVertex3f(x-size,y+size,-size*2);
  glVertex3f(x-size,y-size,-size*2);
  glVertex3f(x-size,y-size,0.0);

  glEnd();
  glBegin(GL_POLYGON);
  //right
  glNormal3f(1, 0, 0);
  glVertex3f(x+size,y+size,-size*2);
  glVertex3f(x+size,y+size,0.0);
  glVertex3f(x+size,y-size,0.0);
  glVertex3f(x+size,y-size,-size*2);

  glEnd();
  glBegin(GL_POLYGON);
  //background
  glNormal3f(0, 0, -1);
  glVertex3f(x+size,y+size,-size*2);
  glVertex3f(x+size,y-size,-size*2);
  glVertex3f(x-size,y-size,-size*2);
  glVertex3f(x-size,y+size,-size*2);

  glEnd();
  glBegin(GL_POLYGON);
  //bottom
  glNormal3f(0, -1, 0);
  glVertex3f(x-size,y-size,0.0);
  glVertex3f(x-size,y-size,-size*2);
   glVertex3f(x+size,y-size,-size*2);
  glVertex3f(x+size,y-size,0.0);

  glEnd();
}
}


void display()
{
  // This function is called whenever it is time to render
  //  a new frame; due to the idle()-function below, this
  //  function will get called several times per second

  // Clear framebuffer & zbuffer
  glClearColor(0.3, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  GLfloat mat_shininess[] = { 50.0 };
  GLfloat mat_diffuseColor[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_specularColor[] = { 1.0, 1.0, 1.0, 1.0 };
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuseColor);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specularColor);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90, 1, 0.01, 100);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
 
  glLoadMatrixd(getObjectMatrix());

  // Enable Gouraud shading
  glShadeModel(GL_SMOOTH);

  // Draw polygon
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  drawCubes();
  // Swap front- and backbuffers
  glutSwapBuffers();
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

  // Register our display- and idle-functions with GLUT
  glutDisplayFunc(display);
  glutIdleFunc(idle);

  // Enter GLUT's main loop; this function will never return
  glutMainLoop();

  return 0;
}
