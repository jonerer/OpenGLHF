
#include <GL/glut.h>
#include <math.h>

#include "helpers.h"

GLuint textureId;

void init()
{
  textureId = loadTexture("../textures/BrickModernLarge0119_S.jpg");
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
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  GLfloat light_position[] = { 0.0, 0.0, 1.0, 1.0 };
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

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureId);

 glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glBegin(GL_POLYGON);
  //framsida
  glNormal3f(0,0,1);
  glColor3f(1, 0, 0);
  glTexCoord2f(0, 0);
  glVertex3f(-0.1, 0.1, 0.0);
  glColor3f(0, 1, 0);
  glTexCoord2f(0, 1);
  glVertex3f(-0.1,-0.1, 0.0);
  glColor3f(0, 0, 1);
  glTexCoord2f(1, 1);
  //glTexCoord2f(getElapsedTime(), 1);
  glVertex3f(0.1,-0.1, 0.0);
  glColor3f(1, 0, 1);
  glTexCoord2f(1, 0);
  //glTexCoord2f(getElapsedTime(), 0);  
  glVertex3f(0.1, 0.1, 0.0);

  glEnd();
  glBegin(GL_POLYGON);
  //TOP
  glNormal3f(0, 1, 0);
  glColor3f(0, 1, 1);
  glTexCoord2f(0, 0);
  glVertex3f(-0.1, 0.1, 0.0);
  glColor3f(1, 1, 0);
  glTexCoord2f(0, 1);
  glVertex3f(0.1, 0.1, 0.0);
  glColor3f(1, 1, 1);
  glTexCoord2f(1, 1);
  glVertex3f(0.1,0.1,-0.2);
  glColor3f(0.3, 0.6, 1);
  glTexCoord2f(1, 0);
  glVertex3f(-0.1,0.1,-0.2);

  glEnd();
  glBegin(GL_POLYGON);
  //left
  glNormal3f(-1, 0, 0);
  glColor3f(0,0.4,0.7);
  glTexCoord2f(0, 0);
  glVertex3f(-0.1,0.1,0.0);
  glColor3f(0.6,0.3,0.0);
  glTexCoord2f(0, 1);
  glVertex3f(-0.1,0.1,-0.2);
  glColor3f(0.2,1.0,0.0);
  glTexCoord2f(1, 1);
  glVertex3f(-0.1,-0.1,-0.2);
  glColor3f(1.0,0.4,0.4);
  glTexCoord2f(1, 0);
  glVertex3f(-0.1,-0.1,0.0);

  glEnd();
  glBegin(GL_POLYGON);
  //right
  glNormal3f(1, 0, 0);
  glColor3f(0,0.9,0.3);
  glTexCoord2f(0, 0);
  glVertex3f(0.1,0.1,-0.2);
  glColor3f(0.2,0.4,0.7);
  glTexCoord2f(0, 1);
  glVertex3f(0.1,0.1,0.0);
  glColor3f(0.5,0,0.7);
  glTexCoord2f(1, 1);
  glVertex3f(0.1,-0.1,0.0);
  glColor3f(0,0.3,0.8);
  glTexCoord2f(1, 0);
  glVertex3f(0.1,-0.1,-0.2);

  glEnd();
  glBegin(GL_POLYGON);
  //background
  glNormal3f(0, 0, -1);
  glColor3f(1,0.2,0.7);
  glTexCoord2f(0, 0);
  glVertex3f(0.1,0.1,-0.2);
  glColor3f(1,0.5,0.3);
  glTexCoord2f(0, 1);
  glVertex3f(0.1,-0.1,-0.2);
  glColor3f(0,0.9,0.7);
  glTexCoord2f(1, 1);
  glVertex3f(-0.1,-0.1,-0.2);
  glColor3f(0,0.1,0.7);
  glTexCoord2f(1, 0);
  glVertex3f(-0.1,0.1,-0.2);

  glEnd();
  glBegin(GL_POLYGON);
  //bottom
  glNormal3f(0, -1, 0);
  glColor3f(0.2,0.8,0.7);
  glTexCoord2f(0, 0);
  glVertex3f(-0.1,-0.1,0.0);
  glColor3f(0.6,0.1,0.2);
  glTexCoord2f(0, 1);
  glVertex3f(-0.1,-0.1,-0.2);
  glColor3f(1,0.4,0.2);
  glTexCoord2f(1, 1);
  glVertex3f(0.1,-0.1,-0.2);
  glColor3f(0.1,0.4,1);
  glTexCoord2f(1, 0);
  glVertex3f(0.1,-0.1,0.0);

  glEnd();



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
