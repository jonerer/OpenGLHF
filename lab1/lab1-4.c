
#include <GL/glut.h>
#include <math.h>

#include "helpers.h"
GLuint textureId;
GLuint textureId2;
GLuint megatextureId[2];
float xwidth;
float yheight;
float zdepth;
float starsize;
float starOffsetX, starOffsetY, starDepth;
void init()


{
  // Place one-time initialization code here
textureId = loadTexture("../textures/Space.jpg");
megatextureId[0] = loadTexture("../textures/megamanmask.jpg");
megatextureId[1] = loadTexture("../textures/megaman.jpg");
}


void display()
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
  glBindTexture(GL_TEXTURE_2D, textureId);
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


//make megaman :D
glEnable(GL_TEXTURE_2D);
glEnable(GL_BLEND);  
glDisable(GL_DEPTH_TEST);
glBlendFunc(GL_DST_COLOR,GL_ZERO);
float textureStart =0.0;
float textureFinish =1.0;
float tS = textureStart;
float tF = textureFinish;
glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP);
glBindTexture(GL_TEXTURE_2D, megatextureId[0]);		// Select The First Mask Texture
  glBegin(GL_QUADS);					// Start Drawing A Textured Quad
glTexCoord2f(tS+0.5, tS); 
glVertex3f(0.0, 0.0,  -2.0);	// Bottom Left
glTexCoord2f(tF+0.5, tS); 
glVertex3f(1.45, 0.0,  -2.0);	// Bottom Right
glTexCoord2f(tF, tF); 
glVertex3f(1.45,  1.0,  -2.0);// Top Right
glTexCoord2f(tS, tF); 
glVertex3f(0.0,  1.0,  -2.0);	// Top Left
glEnd();						// Done Drawing The Quad

/*Again we enable blending and select our texture for scene 1. We map this texture on top of it's mask. */
		
glBlendFunc(GL_ONE, GL_ONE);			// Copy Image 1 Color To The Screen
glBindTexture(GL_TEXTURE_2D, megatextureId[1]);	// Select The First Image Texture
  glBegin(GL_QUADS);				// Start Drawing A Textured Quad
glTexCoord2f(tS, tS); glVertex3f(0.0f, 0.0f,  -2.0f);	// Bottom Left
glTexCoord2f(tF, tS); glVertex3f( 1.45f, 0.0f,  -2.0f);	// Bottom Right
glTexCoord2f(tF, tF); glVertex3f( 1.45f,  1.0f,  -2.0f);	// Top Right
glTexCoord2f(tS, tF); glVertex3f(0.0f,  1.0f,  -2.0f);	// Top Left
	
//glBegin(GL_QUADS);
glEnd();							// Done Drawing The Quad

glDisable(GL_TEXTURE_2D);
glEnable(GL_DEPTH_TEST); 
glDisable(GL_BLEND);



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
  init();

  // Register our display- and idle-functions with GLUT
  glutDisplayFunc(display);
  glutIdleFunc(idle);

  // Enter GLUT's main loop; this function will never return
  glutMainLoop();

  return 0;
}
