
#include <GL/glut.h>
#include <math.h>

#include "helpers.h"
#include "cube.h"

GLuint textureId;
Model* windmill[4];
Model* bunny;
Model* klingoff;

int MILL_BLADE = 0;
int MILL_BALCONY = 1;
int MILL_ROOF = 2;
int MILL_WALLS = 3;
GLuint ss[6];

void init()
{
  // Place one-time initialization code here
  textureId = loadTexture("../textures/BrickModernLarge0119_S.jpg");
  windmill[MILL_BLADE] = loadModel("../models/windmill/blade.obj");
  windmill[MILL_BALCONY] = loadModel("../models/windmill/windmill-balcony.obj");
  windmill[MILL_ROOF] = loadModel("../models/windmill/windmill-roof.obj");
  windmill[MILL_WALLS] = loadModel("../models/windmill/windmill-walls.obj");

  klingoff = loadModel("../models/various/klingon.obj");
  bunny = loadModel("../models/various/bunny.obj");


  //skybox
  ss[0] = loadTexture("../cubemaps/cubemap_berkeley/berkeley_negative_z.jpg"); // back
  ss[1] = loadTexture("../cubemaps/cubemap_berkeley/berkeley_negative_y.jpg"); // podbot
  ss[2] = loadTexture("../cubemaps/cubemap_berkeley/berkeley_positive_x.jpg"); // right
  ss[3] = loadTexture("../cubemaps/cubemap_berkeley/berkeley_negative_x.jpg"); // left
  ss[4] = loadTexture("../cubemaps/cubemap_berkeley/berkeley_positive_z.jpg"); // front
  ss[5] = loadTexture("../cubemaps/cubemap_berkeley/berkeley_positive_y.jpg"); // top
}


void drawSkybox()
{
glPushMatrix();
GLdouble lol[16]; 
int i = 0;
for(i = 0; i<16; i++) {
lol[i]= getCameraMatrix()[i];
}
lol[12] = 0;
lol[13] = 0;
lol[14] = 0;
glLoadMatrixd(lol);
glDisable(GL_DEPTH_TEST);
float hf = 50;
glBindTexture(GL_TEXTURE_2D, ss[4]);
  glBegin(GL_POLYGON);
glColor3f(1, 1, 1); 
  //baksida
  glNormal3f(0,0,1);
   glTexCoord2f(0, 0);
  glVertex3f(-hf, hf, -hf);
  glTexCoord2f(0, 1);
  glVertex3f(-hf,-hf, -hf);
  glTexCoord2f(1, 1);
  //glTexCoord2f(getElapsedTime(), 1);
  glVertex3f(hf,-hf, -hf);
  glTexCoord2f(1, 0);
  //glTexCoord2f(getElapsedTime(), 0);  
  glVertex3f(hf, hf, -hf);
  glEnd();
glBindTexture(GL_TEXTURE_2D, ss[1]);
  glBegin(GL_POLYGON);
  //BOT
  glNormal3f(0, 1, 0);
  glTexCoord2f(0, 0);
  glVertex3f(-hf, -hf, -hf);
  glTexCoord2f(0, 1);
  glVertex3f(-hf, -hf, hf);
  glTexCoord2f(1, 1);
  glVertex3f(hf,-hf,hf);
   glTexCoord2f(1, 0);
  glVertex3f(hf,-hf,-hf);
  glEnd();
glBindTexture(GL_TEXTURE_2D, ss[2]);
  glBegin(GL_POLYGON);
  //right
  glNormal3f(-1, 0, 0);
  glTexCoord2f(0, 0);
  glVertex3f(hf,hf,-hf);
  glTexCoord2f(0, 1);
  glVertex3f(hf,-hf,-hf);
  glTexCoord2f(1, 1);
  glVertex3f(hf,-hf,hf);
  glTexCoord2f(1, 0);
  glVertex3f(hf,hf,hf);
  glEnd();
glBindTexture(GL_TEXTURE_2D, ss[3]);
  glBegin(GL_POLYGON);
  //left
  glNormal3f(1, 0, 0);
  glTexCoord2f(0, 0);
  glVertex3f(-hf,hf,hf);
  glTexCoord2f(0, 1);
  glVertex3f(-hf,-hf,hf);
  glTexCoord2f(1, 1);
  glVertex3f(-hf,-hf,-hf);
  glTexCoord2f(1, 0);
  glVertex3f(-hf,hf,-hf);
  glEnd();
glBindTexture(GL_TEXTURE_2D, ss[0]);
  glBegin(GL_POLYGON);
  //front
  glNormal3f(0, 0, -1);
  glTexCoord2f(0, 0);
  glVertex3f(hf,hf,hf);
  glTexCoord2f(0, 1);
  glVertex3f(hf,-hf,hf);
  glTexCoord2f(1, 1);
  glVertex3f(-hf,-hf,hf);
  glTexCoord2f(1, 0);
  glVertex3f(-hf,hf,hf);
  glEnd();
glBindTexture(GL_TEXTURE_2D, ss[5]);
  glBegin(GL_POLYGON);
//top
  glNormal3f(0, -1, 0);
  glTexCoord2f(0, 0);
  glVertex3f(-hf,hf,hf);
  glTexCoord2f(0, 1);
  glVertex3f(-hf,hf,-hf);
  glTexCoord2f(1, 1);
  glVertex3f(hf,hf,-hf);
  glTexCoord2f(1, 0);
  glVertex3f(hf,hf,hf);
  glEnd();
glEnable(GL_DEPTH_TEST);
glPopMatrix();
}

void drawWindmill() {
  glPushMatrix();
  int to_draw;
  float spin_speed = 90;
  for (to_draw = 1; to_draw < 4; to_draw++) {
    if (MILL_WALLS == to_draw) {
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    glColor3f(0.8, 0+to_draw*0.2, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, windmill[to_draw]->vertexArray);
    glNormalPointer(GL_FLOAT, 0, windmill[to_draw]->normalArray);
    glDrawElements(GL_TRIANGLES, windmill[to_draw]->numIndices, GL_UNSIGNED_INT, windmill[to_draw]->indexArray);
    if (to_draw == MILL_WALLS) {
      glDisable(GL_BLEND);
    }
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
  glPopMatrix();
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
  GLfloat light_position[] = { 0.0, 0.0, -1.0, 0.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  //glLoadMatrixd(getCameraMatrix());
  GLfloat light_position1[] = { -10.0, 10.0, 20.0, 1.0 };
  glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

  GLfloat ambientColor [] = { 0.0, 0.0, 0.0, 0.0 };
  GLfloat diffuseColor[] = { 0.0, 1.0, 1.0, 1.0 };
  GLfloat specularColor[] = { 1.0, 1.0, 1.0, 1.0 };
  glLightfv(GL_LIGHT1, GL_AMBIENT, ambientColor);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseColor);
  glLightfv(GL_LIGHT1, GL_SPECULAR, specularColor);

  //Enable lighting and light 0
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_NORMALIZE);

  // Set default material properties
  GLfloat mat_shininess[] = { 50.0 };
  GLfloat mat_diffuseColor[] = { 1.0, 0.0, 1.0, 0.6 };
  GLfloat mat_specularColor[] = { 1.0, 1.0, 0.0, 0.6 };

  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuseColor);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specularColor);

  // Setup projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90, 1, 0.01, 500);

  // Setup object matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glLoadMatrixd(getCameraMatrix());

  // Enable Z-buffering
  glEnable(GL_DEPTH_TEST);

  // Enable Gouraud shading
  glShadeModel(GL_SMOOTH);

  // Enable texturing
  glEnable(GL_TEXTURE_2D);



  // Enable backface culling
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  drawSkybox();

// the floooor  
  glBindTexture(GL_TEXTURE_2D, textureId);
  int more_floor = 200;
  int mf = more_floor;
  glBegin(GL_POLYGON);
  glNormal3f(0,1,0);
  glTexCoord2f(0, 0);
  glVertex3f(-mf,0, -mf);
  glTexCoord2f(0, 1);
  glVertex3f(-mf,0, mf);
  glTexCoord2f(1, 1);
  glVertex3f(mf,0, mf);
  glTexCoord2f(1,0);
  glVertex3f(mf, 0, -mf);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  glPushMatrix();
  //glRotatef(-56, 0, 0, 1);
  glTranslatef(0, 10*fabs(sin(3.14*getElapsedTime()))+2.5, 30);
  glRotatef((360*getElapsedTime()) / 6, 0, 1, 0);
  glTranslatef(-80, 0, -80);
  glRotatef(-45, 0, 1, 0);
  glScalef(5, 5, 5);
  //glRotatef(0, 1, 0, to_draw * 90);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, bunny->vertexArray);
  glNormalPointer(GL_FLOAT, 0, bunny->normalArray);
  glDrawElements(GL_TRIANGLES, bunny->numIndices, GL_UNSIGNED_INT, bunny->indexArray);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(50, 0, 75);
  glRotatef(-56, 1, 1, 0);
  glScalef(30, 30, 30);
  //glRotatef(0, 1, 0, to_draw * 90);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, klingoff->vertexArray);
  glNormalPointer(GL_FLOAT, 0, klingoff->normalArray);
  glDrawElements(GL_TRIANGLES, klingoff->numIndices, GL_UNSIGNED_INT, klingoff->indexArray);
  glPopMatrix();
 
  glPushMatrix();
  drawWindmill();
  glTranslatef(25,0,0);
  drawWindmill();
  glTranslatef(-50,0,40);
  drawWindmill();
  glPopMatrix();
  // Draw cube using array-based API



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
