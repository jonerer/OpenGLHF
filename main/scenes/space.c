
#include <GL/glut.h>
#include <math.h>
#include "../helpers.h"
#include <stdio.h>									
								

GLuint spacetextureId;
GLuint megatextureId[2];

float xwidth;
float yheight;
float zdepth;
float starsize;
float starOffsetX, starOffsetY, starDepth;
void space_init()
{
  // Place one-time initialization code here
spacetextureId = loadTexture("textures/Space.jpg");
megatextureId[0] = loadTexture("textures/Openglhf.jpg");
megatextureId[1] = loadTexture("textures/mixed.jpg");
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
  glClearColor(0, 0, 0, 0);
  glClearDepth(1.0);
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
  starDepth = zdepth-460;


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

glTranslatef(-getElapsedTime()*200,0,0);

float megaDepth = zdepth;
float megaheight = yheight;
float megaWidth = xwidth*5;
float textureStart =0.0;
float textureFinish =1.0;
float tS = textureStart;
float tF = textureFinish;


glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, megatextureId[1]);

glBegin(GL_QUADS);				// Start Drawing A Textured Quad
glTexCoord2f(tF, tF);
glVertex3f(megaWidth, -megaheight-160.0f,-megaDepth);	// Bottom Left
glTexCoord2f(tS, tF);
glVertex3f(megaWidth+1000.0f,-megaheight-160.0f,-megaDepth);	// Bottom Right
glTexCoord2f(tS, tS);
glVertex3f(megaWidth+1000.0f,-megaheight,-megaDepth);	// Top Right
 glTexCoord2f(tF, tS);
glVertex3f(megaWidth,-megaheight,-megaDepth);	// Top Left
glEnd();



megaWidth = xwidth*3;

glBindTexture(GL_TEXTURE_2D, megatextureId[0]);

glBegin(GL_QUADS);
glTexCoord2f(tS, tF);				// Start Drawing A Textured Quad
glVertex3f(megaWidth, megaheight,-megaDepth);	// Bottom Left
glTexCoord2f(tF, tF);
glVertex3f(megaWidth+1000.0f,megaheight,-megaDepth);	// Bottom Right
 glTexCoord2f(tF, tS);
glVertex3f(megaWidth+1000.0f,megaheight+160.0f,-megaDepth);	// Top Right
glTexCoord2f(tS, tS);
glVertex3f(megaWidth,megaheight+160.0f,-megaDepth);	// Top Left
glEnd();

//************************STAR START************************************//
/*
glDisable(GL_DEPTH_TEST);
glEnable(GL_TEXTURE_2D);
glEnable(GL_BLEND);  
glBlendFunc(GL_DST_COLOR,GL_ZERO);
float megaDepth = zdepth;
float megaheight = yheight;
float megaWidth = xwidth;
float textureStart =0.0;
float textureFinish =1.0;
float tS = textureStart;
float tF = textureFinish;
float xXx = 0.44;
glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP);
glBindTexture(GL_TEXTURE_2D, megatextureId[0]);		// Select The First Mask Texture
glBegin(GL_QUADS);				// Start Drawing A Textured Quad
glTexCoord2f(xXx+tF, tF);
glVertex3f(megaWidth, -megaheight,-megaDepth);	// Bottom Left
glTexCoord2f(xXx+tS, tF);
glVertex3f(megaWidth+160.0f, -megaheight,-megaDepth);	// Bottom Right
glTexCoord2f(xXx+tS+0.5, tS);
glVertex3f(megaWidth+160.0f,  -megaheight+160.0f,-megaDepth);	// Top Right
 glTexCoord2f(xXx+tF+0.5, tS);
glVertex3f(megaWidth,  -megaheight+160.0f,-megaDepth);	// Top Left
glEnd();

*/

/*Again we enable blending and select our texture for scene 1. We map this texture on top of it's mask. */
	/*	
glBlendFunc(GL_ONE, GL_ONE);			// Copy Image 1 Color To The Screen
glBindTexture(GL_TEXTURE_2D, megatextureId[1]);	// Select The First Image Texture
glBegin(GL_QUADS);				// Start Drawing A Textured Quad
glTexCoord2f(xXx+tF, tF);
glVertex3f(megaWidth, -megaheight,-megaDepth);	// Bottom Left
glTexCoord2f(xXx+tS, tF);
glVertex3f(megaWidth+160.0f, -megaheight,-megaDepth);	// Bottom Right
glTexCoord2f(xXx+tS+0.5, tS);
glVertex3f(megaWidth+160.0f,  -megaheight+160.0f,-megaDepth);	// Top Right
 glTexCoord2f(xXx+tF+0.5, tS);
glVertex3f(megaWidth,  -megaheight+160.0f,-megaDepth);	// Top Left
glEnd();

glDisable(GL_TEXTURE_2D);
glEnable(GL_DEPTH_TEST); 
glDisable(GL_BLEND);
*/
//************************STAR END************************************//

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


/*
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
*/
