
#include <GL/glut.h>
#include <math.h>

#include "helpers.h"
#include "cube.h"

GLuint textureId;
Model* windmill[4];

int MILL_BLADE = 0;
int MILL_BALCONY = 1;
int MILL_ROOF = 2;
int MILL_WALLS = 3;

void init()
{
  // Place one-time initialization code here
  //textureId = loadTexture("../models/LittleNell/Tree/tree.jpg");
  windmill[MILL_BLADE] = loadModel("../models/windmill/blade.obj");
  windmill[MILL_BALCONY] = loadModel("../models/windmill/windmill-balcony.obj");
  windmill[MILL_ROOF] = loadModel("../models/windmill/windmill-roof.obj");
  windmill[MILL_WALLS] = loadModel("../models/windmill/windmill-walls.obj");
  //bunny = loadModel("../models/LittleNell/Tree/tree.obj");
}

void display()
{
  // This function is called whenever it is time to render
  //  a new frame; due to the idle()-function below, this
  //  function will get called several times per second

  // Clear framebuffer & zbuffer
  glClearColor(0.3, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Position light 0
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  // Enable lighting and light 0
  //glEnable(GL_LIGHTING);
  //glEnable(GL_LIGHT0);
  //glEnable(GL_NORMALIZE);

  // Set default material properties
  GLfloat mat_shininess[] = { 50.0 };
  GLfloat mat_diffuseColor[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_specularColor[] = { 1.0, 1.0, 1.0, 1.0 };

  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuseColor);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specularColor);

  // Setup projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90, 1, 0.01, 100);

  // Setup object matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glLoadMatrixd(getCameraMatrix());

  // Enable Z-buffering
  glEnable(GL_DEPTH_TEST);

  // Enable Gouraud shading
  glShadeModel(GL_SMOOTH);

  // Enable backface culling
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  // Enable texturing
  //glEnable(GL_TEXTURE_2D);
  //glBindTexture(GL_TEXTURE_2D, textureId);
//

  // Draw cube using array-based API

  int to_draw;
  float spin_speed = 90;
  for (to_draw = 1; to_draw < 4; to_draw++) {
    glColor3f(0.8, 0+to_draw*0.2, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, windmill[to_draw]->vertexArray);
    glNormalPointer(GL_FLOAT, 0, windmill[to_draw]->normalArray);
    glDrawElements(GL_TRIANGLES, windmill[to_draw]->numIndices, GL_UNSIGNED_INT, windmill[to_draw]->indexArray);
  }
  glTranslatef(4.6, 9.15, 0);
  glRotatef(getElapsedTime()*spin_speed, 1, 0, 0);  

  glPushMatrix();
  glColor3f(0.8, 0, 0.4);
  glRotatef(0, 1, 0, 0);
  //glRotatef(0, 1, 0, to_draw * 90);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, windmill[0]->vertexArray);
  glNormalPointer(GL_FLOAT, 0, windmill[0]->normalArray);
  glDrawElements(GL_TRIANGLES, windmill[0]->numIndices, GL_UNSIGNED_INT, windmill[0]->indexArray);
  glPopMatrix();
  
  glPushMatrix();
  glColor3f(0.8, 0, 0.4);
  glRotatef(90, 1, 0, 0);
  //glRotatef(0, 1, 0, to_draw * 90);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, windmill[0]->vertexArray);
  glNormalPointer(GL_FLOAT, 0, windmill[0]->normalArray);
  glDrawElements(GL_TRIANGLES, windmill[0]->numIndices, GL_UNSIGNED_INT, windmill[0]->indexArray);
  glPopMatrix();
  
  glPushMatrix();
  glColor3f(0.8, 0, 0.4);
  glRotatef(180, 1, 0, 0);
  //glRotatef(0, 1, 0, to_draw * 90);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, windmill[0]->vertexArray);
  glNormalPointer(GL_FLOAT, 0, windmill[0]->normalArray);
  glDrawElements(GL_TRIANGLES, windmill[0]->numIndices, GL_UNSIGNED_INT, windmill[0]->indexArray);
  glPopMatrix();
  
  glPushMatrix();
  glColor3f(0.8, 0, 0.4);
  glRotatef(270, 1, 0, 0);
  //glRotatef(0, 1, 0, to_draw * 90);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, windmill[0]->vertexArray);
  glNormalPointer(GL_FLOAT, 0, windmill[0]->normalArray);
  glDrawElements(GL_TRIANGLES, windmill[0]->numIndices, GL_UNSIGNED_INT, windmill[0]->indexArray);
  glPopMatrix();

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
