
#include <GL/glut.h>
#include <math.h>

#include "helpers.h"

GLuint groundTexture;
int height, width;
unsigned char *imagedata;

void renderGround()
{
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  
// Your terrain should match this flat quad
  
  glBegin(GL_POLYGON);
  glNormal3f(0, 1, 0);
  glTexCoord2f(0, 10);
  glVertex3f(-100, -0.01, 100);
  glTexCoord2f(0, 0);
  glVertex3f(100, -0.01, 100);
  glTexCoord2f(10, 0);
  glVertex3f(100, -0.01, -100);
  glTexCoord2f(10, 10);
  glVertex3f(-100, -0.01, -100);
  glEnd();
  glPopAttrib();
}


void renderTerrain()
{
int row,col;
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  int sideLength = 200;
  // set texLength to 20.ssss
  int texLength = 20;

  float heightNodes = height - 1;
  float widthNodes = width - 1;

    for (row = 0; row < heightNodes; row++)	{
      for (col = 0; col < widthNodes; col++) {
float xLow = row*(sideLength/widthNodes) - sideLength / 2;
float xHigh = (row+1)*(sideLength/widthNodes) - sideLength / 2;

float zLow = col*(sideLength/heightNodes) - sideLength / 2;
float zHigh = (col+1)*(sideLength/heightNodes) - sideLength / 2;

float heightDivisorer = 5;

float texnumb = sideLength/widthNodes / texLength;

glPushMatrix();
glTranslatef(0, 10, 0);
glBegin(GL_POLYGON);
//First triangle
glTexCoord2f(0, 0);
glVertex3f(xLow, (int)imagedata[(row*width + col)*3] / heightDivisorer, zLow);
glTexCoord2f(0, texnumb);
glVertex3f(xHigh, (int)imagedata[((row+1)*width + col)*3] / heightDivisorer, zLow);
glTexCoord2f(texnumb, 0);
glVertex3f(xLow , (int)imagedata[(row*width + col+1)*3] / heightDivisorer, zHigh);
glEnd();
glBegin(GL_POLYGON);
//Second triangle
glTexCoord2f(texnumb, 0);
glVertex3f(xLow , (int)imagedata[(row*width + col + 1)*3] / heightDivisorer, zHigh);
glTexCoord2f(texnumb, texnumb);
glVertex3f(xHigh, (int)imagedata[((row+1)*width + col)*3] / heightDivisorer, zLow);
glTexCoord2f(0, texnumb);
glVertex3f(xHigh, (int)imagedata[((row+1)*width + col + 1)*3] / heightDivisorer, zHigh);
glEnd();
glPopMatrix();


        //printf("(%d, %d): height: %d\n", row, col, (int)imagedata[(row*width + col)*3]);
      }
    }

  glPopAttrib();
	// YOU SHOULD WRITE THIS!
	//The height map image is available to you as a data array. Figure out a way to draw it in 3D.
	//Hint: The initial heightmap is extremely small. This is to help you. Use printf as needed.
	//Hint: Make a double "for" loop over the array, with appropriate scaling for height and width so your terrain matches the given quad.
	//Hint: Every quad is drawn as two triangles. Do each triangle separately, so you have full control.
}

// Light and materials
  GLfloat light_position[] = { 0.0, 1.0, 0.0, 0.0 }; // Directional from above
  GLfloat mat_shininess[] = { 50.0 };
  GLfloat mat_diffuseColor[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_specularColor[] = { 1.0, 1.0, 1.0, 1.0 };

void display()
{
  // This function is called whenever it is time to render
  // a new frame; due to the idle()-function below, this
  // function will get called several times per second
  
  // Clear framebuffer & zbuffer
  glClearColor(0.3, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Set current material  
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuseColor);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specularColor);
  
  // Place camera and light
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
//  gluLookAt(100,50,50, 0, 0, 0, 0, 1, 0); // No manual control but better place from the start
  glLoadMatrixd(getCameraMatrix());
  glLightfv(GL_LIGHT0, GL_POSITION, light_position); // After camera matrix - camera independent!
  
  // Render the scene!
  renderGround();
  renderTerrain();
  
  // Swap front- and backbuffers
  glutSwapBuffers();
}

void init()
{
  int row, col;
  // An ordinary texture
  groundTexture = loadTexture("../textures/TropicalFoliage0025_1_S.jpg");
  
  // A heightmap image
  imagedata = readppm("heightmaps/TERRA2.PPM", &height, &width);
//  imagedata = readppm("../../../heightmaps/fft-terrain.ppm", &height, &width);

  // Print out image contents.
  // Warning! Only do this for small images or you will get incredible amounts of data!

  if (width < 16)
    for (row = 0; row < height; row++)
      for (col = 0; col < width; col++)
      {
        printf("(%d, %d): R = %d, G = %d, B = %d\n", row, col, (int)imagedata[(row*width + col)*3], (int)imagedata[(row*width + col)*3+1], (int)imagedata[(row*width + col)*3+2]);
      }
  // Use the imagedata array for heights in the terrain!

// GL inits
  glDisable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH); // Enable Gouraud shading
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, groundTexture);
}

void timer(int i)
{
	glutTimerFunc(20, timer, i);
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
  glutCreateWindow("Lab 4");

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90, 1, 0.01, 1000);
  glMatrixMode(GL_MODELVIEW);
  
  initHelperLibrary();
  init();

  // Register our display- and idle-functions with GLUT
  glutDisplayFunc(display);
  glutTimerFunc(20, timer, 0);

  // Enter GLUT's main loop; this function will never return
  glutMainLoop();

  return 0;
}

