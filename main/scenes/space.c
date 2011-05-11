
#include <GL/glut.h>
#include <math.h>

#include "helpers.h"
GLuint spacetextureId;

float xwidth;
float yheight;
float zdepth;
float starsize;
float starOffsetX, starOffsetY, starDepth;
void space_init()


{
  // Place one-time initialization code here
spacetextureId = loadTexture("../textures/Space.jpg");

}

void space_load() {
  printf("lolspace\n");
}
void space_disp()
{
  // This function is called whenever it is time to render
  //  a new frame; due to the idle()-function below, this
  //  function will get called several times per second


  // Clear framebuffer & zbuffer
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90, 1, 0.01, 1500);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
  //gluLookAt(0,0,0,getElapsedTime(),0,-1, 0, 1, 0); 


  glLoadMatrixd(getObjectMatrix());
  // Enable Gouraud shading
  glShadeModel(GL_SMOOTH);
  
  // Draw polygon
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  //load texture
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, spacetextureId);
  glBegin(GL_POLYGON);
  
/*
  //size of wall
  float zdepth = 390.0;
  float xwidth = 600;
  float yheight = 300.0;


  //do the wall 
  glColor3f(1, 1, 1);
  glNormal3f(0,0,1);
  glTexCoord2f(0, 1);
  glVertex3f(-xwidth, yheight, -zdepth);
  glTexCoord2f(0, 0);
  glVertex3f(-xwidth,-yheight, -zdepth);
  glTexCoord2f(1, 0);
  glVertex3f(xwidth,-yheight, -zdepth);
  glTexCoord2f(1, 1);
  glVertex3f(xwidth, yheight, -zdepth);
  glEnd();
*/

//Scrolling through texcoords

  //size of wall
  zdepth = 590.0;
  xwidth = 600;
  yheight = 400.0;
  starDepth = zdepth-40;


  //do the wall 
  glColor3f(1, 1, 1);
  glNormal3f(0,0,1);
  glTexCoord2f(getElapsedTime()/200, 1);
  glVertex3f(-xwidth, yheight, -zdepth);
  glTexCoord2f(getElapsedTime()/200, 0);
  glVertex3f(-xwidth,-yheight, -zdepth);
  glTexCoord2f(0.3+getElapsedTime()/200, 0);
  glVertex3f(xwidth,-yheight, -zdepth);
  glTexCoord2f(0.3+getElapsedTime()/200, 1);
  glVertex3f(xwidth, yheight, -zdepth);
  glEnd();

glDisable(GL_TEXTURE_2D);
//Do the bioduk top and bot
  glBegin(GL_POLYGON);
 glColor3f(0.9,0.9,0.9);
  glVertex3f(-xwidth,yheight+5,-zdepth+1);
  glVertex3f(-xwidth,yheight,-zdepth+1);
  glVertex3f(xwidth,yheight,-zdepth+1);
  glVertex3f(xwidth,yheight+5,-zdepth+1);
  glEnd();

  glBegin(GL_POLYGON);
glColor3f(0.9,0.9,0.9);
  glVertex3f(-xwidth,-yheight,-zdepth+1);
  glVertex3f(-xwidth,-yheight-5,-zdepth+1);
  glVertex3f(xwidth,-yheight-5,-zdepth+1);
  glVertex3f(xwidth,-yheight,-zdepth+1);
  glEnd();


//the moving stuff :D
glPushMatrix();

glTranslatef(-getElapsedTime()*50,0,0);
//glRotatef(45,0,0,1);

starsize = 15;
  starOffsetX = 0;
  starOffsetY = 0;
//Layer 1 :D

makeEmStars();


//Layer 2 :D
//xwidth = 380;
//yheight =100;
//zdepth = 300;
//makeEmStars(xwidth, yheight, zdepth, starsize);


//Layer 3 :D
//xwidth = 380;
//yheight =100;
//zdepth = 300;
//makeEmStars(xwidth, yheight, zdepth);

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

void makeEmStars() 
{
drawAStar();

starOffsetX = 100;
starOffsetY = 200;
drawAStar();

starOffsetX = -starOffsetX/2;
starOffsetY = -starOffsetY/2;
drawAStar();
}

void drawAStar() {

/*
  glBegin(GL_POLYGON);
  glColor3f(0.9,0.9,0.9);
  glVertex3f(0-starOffsetX,0+starOffsetY,-starDepth);
  glVertex3f(0-starOffsetX,0+starOffsetY-starsize,-starDepth);
  glVertex3f(0+starsize-starOffsetX,0+starOffsetY-starsize,-starDepth);
  glVertex3f(0+starsize-starOffsetX,0+starOffsetY,-starDepth);
  glEnd();

*/

glBegin(GL_POLYGON);
glColor3f(0.9,0.9,0.9);
  glVertex3f(0-starOffsetX,starsize+starOffsetY,-starDepth);
  glVertex3f(-starsize/5-starOffsetX,starsize/5+starOffsetY,-starDepth);
  glVertex3f(-starsize-starOffsetX,starOffsetY,-starDepth);
  glVertex3f(-starsize/4-starOffsetX,-starsize/4+starOffsetY,-starDepth);
  glVertex3f(-starsize/3-starOffsetX,-starsize+starOffsetY,-starDepth);
  glVertex3f(0-starOffsetX, -starsize/4+starOffsetY,-starDepth);
glEnd();

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
  space_init();

  // Register our display- and idle-functions with GLUT
  glutDisplayFunc(space_disp);
  glutIdleFunc(idle);

  // Enter GLUT's main loop; this function will never return
  glutMainLoop();

  return 0;
}
