
#include <GL/glut.h>
#include <math.h>

#include "../helpers.h"
#include "water.h"
#define crossProduct(a,b,c) \
	(a)[0] = (b)[1] * (c)[2] - (c)[1] * (b)[2]; \
	(a)[1] = (b)[2] * (c)[0] - (c)[2] * (b)[0]; \
	(a)[2] = (b)[0] * (c)[1] - (c)[0] * (b)[1];

GLuint ss[6];
GLuint groundTexture;
GLuint fiskautomat;
GLuint waterTexture;
int height, width;
unsigned char *imagedata;

Model* klingoff;
int millis = 0;

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
float hf = 200;
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
void water_renderGround()
{
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, waterTexture);
// Your terrain should match this flat quad
  float waveheight = 2 ;
  glPushMatrix();
  glTranslatef(0, 0.1 + waveheight, 0);
  float phi = 0.1;
  int x = -30;
  for(;x < 60; x++) {
	glBegin(GL_POLYGON);
	glNormal3f(0, 1, 0);
	float height = sin(getElapsedTime()+x*phi) * waveheight;
	float heightplusone = sin(getElapsedTime()+(x+1)*phi) * waveheight;
	float shearing = sin(getElapsedTime()+x*(phi*20)) * waveheight;
	float shearingplusone = sin(getElapsedTime()+(x+1)*(phi*20)) * waveheight;
	glTexCoord2f(0+shearing, 1);

	// now we get the height (plus one)

	glVertex3f(x, height, 100);
	glTexCoord2f(0+shearing, 0);
	glVertex3f(x+1, heightplusone, 100);
	glTexCoord2f(shearingplusone, 100);
	glVertex3f(x+1, heightplusone, -100);
	glTexCoord2f(shearingplusone, 100);
	glVertex3f(x, height, -100);
	glEnd();
  }
  glPopMatrix();
  glPopAttrib();
}

void water_normalize(float* a) {
	float len = sqrt(pow(a[0],2) + pow(a[1],2) + pow(a[2],2));
           a[0] = a[0]/len;
	   a[1] = a[1]/len;
	   a[2] = a[2]/len;
}


void water_renderTerrain()
{
int isLake;
int row,col;
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  int sideLength = 200;
  // set texLength to 20.ssss
  int texLength = 20;

  float heightNodes = height - 1;
  float widthNodes = width - 1;
float heightDivisorer = 3;


float haxPos[] = { -90, 0, 50 };
int quad[] = { ((haxPos[0] + sideLength / 2) / (sideLength/widthNodes))
		, ((haxPos[2] + sideLength / 2) / (sideLength/heightNodes)) };
//printf("quad: %d, %d \n", quad[0], quad[1]);
//printf("heightNodes, Widthnodes, height, width: %f, %f\n", heightNodes, widthNodes);
glBindTexture(GL_TEXTURE_2D, groundTexture);
    for (row = 0; row < heightNodes; row++)	{
      for (col = 0; col < widthNodes; col++) {
//printf("row: %d", row);

float xLow = row*(sideLength/widthNodes) - sideLength / 2;
float xHigh = (row+1)*(sideLength/widthNodes) - sideLength / 2;

float zLow = col*(sideLength/heightNodes) - sideLength / 2;
float zHigh = (col+1)*(sideLength/heightNodes) - sideLength / 2;

float yLowLow = (int)imagedata[(row*width + col)*3] / heightDivisorer;
float yLowHigh = (int)imagedata[(row*width + col+1)*3] / heightDivisorer;
float yHighLow = (int)imagedata[((row+1)*width + col)*3] / heightDivisorer;
float yHighHigh = (int)imagedata[((row+1)*width + col + 1)*3] / heightDivisorer;



float texnumb = sideLength/widthNodes;

glPushMatrix();
glTranslatef(0, 0, 0);
glBegin(GL_POLYGON);
//First triangle
float a[3];
float b[] = {xHigh-xLow,yHighLow-yLowLow , zLow-zLow};
float c[] = {xLow-xLow,yLowHigh-yLowLow, zHigh-zLow};
crossProduct(a, c, b);
water_normalize(a);
glNormal3f(a[0], a[1], a[2]);
glTexCoord2f(0, 0);
glVertex3f(xLow, yLowLow, zLow);
glTexCoord2f(0, texnumb);
glVertex3f(xHigh, yHighLow, zLow);
glTexCoord2f(texnumb, 0);
glVertex3f(xLow , yLowHigh, zHigh);
glEnd();
glBegin(GL_POLYGON);
//Second triangle
float d[] = {xHigh-xLow, yHighLow-yLowHigh, zLow-zHigh};
float e[] = {xHigh-xLow, yHighHigh-yLowHigh, zHigh-zHigh};
crossProduct(a, e, d);
water_normalize(a);
glNormal3f(a[0], a[1], a[2]);
glTexCoord2f(texnumb, 0);
glVertex3f(xLow , yLowHigh, zHigh);
glTexCoord2f(texnumb, texnumb);
glVertex3f(xHigh, yHighLow, zLow);
glTexCoord2f(0, texnumb);
glVertex3f(xHigh, yHighHigh, zHigh);
glEnd();
glPopMatrix();

if(quad[0] == row && quad[1] == col) {
	float botleftDistance = sqrt(pow(quad[0]-xLow,2)+pow(quad[1]-zLow,2));
	float toprightDistance = sqrt(pow(quad[0]-xHigh,2)+pow(quad[1]-zHigh,2));

	//printf("botleftdist: %f, topleftdist: %f\n", botleftDistance, toprightDistance);
	float y = botleftDistance < toprightDistance ? yLowLow : yHighHigh;
	float x = botleftDistance < toprightDistance ? xLow : xHigh;
	float z = botleftDistance < toprightDistance ? zLow : zHigh; 

        //printf("grr: (%d, %f, %d): height: %d\n", row, y, col, (int)imagedata[(row*width + col)*3]);
  glPushMatrix();
  glTranslatef(x, y, z);
  //glRotatef(-56, 1, 1, 0);
  glScalef(1, 1, 1);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, klingoff->vertexArray);
  glNormalPointer(GL_FLOAT, 0, klingoff->normalArray);
  glDrawElements(GL_TRIANGLES, klingoff->numIndices, GL_UNSIGNED_INT, klingoff->indexArray);
  glPopMatrix();
    }
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
  GLfloat light_position[] = { 0.0, 150, 0.0, 1.0 }; // Directional from above
  GLfloat mat_shininess[] = { 50.0 };
  GLfloat mat_diffuseColor[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_specularColor[] = { 1.0, 1.0, 1.0, 1.0 };

void water_disp()
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
  
  millis += 20;
  // Place camera and light
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0,6,-50 + (float)millis / 100, -5, 0, 0 + (float)millis / 300, 0, 1, 0); // No manual control but better place from the start
  //glLoadMatrixd(getCameraMatrix());
  glLightfv(GL_LIGHT0, GL_POSITION, light_position); // After camera matrix - camera independent!

  
  // Render the scene!
  drawSkybox();
  water_renderGround();
  //water_renderTerrain();
  // Swap front- and backbuffers
  glutSwapBuffers();
 }

void water_load()
{
  // An ordinary texture
  groundTexture = loadTexture("textures/TropicalFoliage0025_1_S.jpg");
  waterTexture = loadTexture("textures/water_deep.jpg");
  fiskautomat = loadTexture("textures/fiskautomat.jpg");
    //klingoff = loadModel("models/various/klingon.obj");
  // A heightmap image
  imagedata = readppm("heightmaps/fft-terrain.ppm", &height, &width);

  //skybox
/*  
ss[0] = loadTexture("../cubemaps/cubemap_berkeley/berkeley_negative_z.jpg"); // back
  ss[1] = loadTexture("../cubemaps/cubemap_berkeley/berkeley_negative_y.jpg"); // podbot
  ss[2] = loadTexture("../cubemaps/cubemap_berkeley/berkeley_positive_x.jpg"); // right
  ss[3] = loadTexture("../cubemaps/cubemap_berkeley/berkeley_negative_x.jpg"); // left
  ss[4] = loadTexture("../cubemaps/cubemap_berkeley/berkeley_positive_z.jpg"); // front
  ss[5] = loadTexture("../cubemaps/cubemap_berkeley/berkeley_positive_y.jpg"); // top
*/
/*
  ss[0] = loadTexture("cubemaps/cubemap_grid/cubemap_grid_512.jpg"); // back
  ss[1] = loadTexture("cubemaps/cubemap_grid/cubemap_grid_512.jpg"); // podbot
  ss[2] = loadTexture("cubemaps/cubemap_grid/cubemap_grid_512.jpg"); // right
  ss[3] = loadTexture("cubemaps/cubemap_grid/cubemap_grid_512.jpg"); // left
  ss[4] = loadTexture("cubemaps/cubemap_grid/cubemap_grid_512.jpg"); // front
  ss[5] = loadTexture("cubemaps/cubemap_grid/cubemap_grid_512.jpg"); // top
*/
/*
  ss[0] = loadTexture("cubemaps/cubemap_dots/dots_positive_x.jpg"); // back
  ss[1] = loadTexture("cubemaps/cubemap_dots/dots_negative_y.jpg"); // podbot
  ss[2] = loadTexture("cubemaps/cubemap_dots/dots_positive_x.jpg"); // right
  ss[3] = loadTexture("cubemaps/cubemap_dots/dots_negative_x.jpg"); // left
  ss[4] = loadTexture("cubemaps/cubemap_dots/dots_positive_z.jpg"); // front
  ss[5] = loadTexture("cubemaps/cubemap_dots/dots_positive_y.jpg"); // top
*/

  ss[0] = loadTexture("cubemaps/black-wallpaper.jpg"); // back
  ss[1] = loadTexture("cubemaps/black-wallpaper.jpg"); // podbot
  ss[2] = loadTexture("cubemaps/black-wallpaper.jpg"); // right
  ss[3] = loadTexture("cubemaps/black-wallpaper.jpg"); // left
  ss[4] = loadTexture("cubemaps/black-wallpaper.jpg"); // front
  ss[5] = loadTexture("cubemaps/black-wallpaper.jpg"); // top




}

void water_init()
{
  int row, col;

  // Print out image contents.
  // Warning! Only do this for small images or you will get incredible amounts of data!

  if (width < 16)
    for (row = 0; row < height; row++)
      for (col = 0; col < width; col++)
      {
        // printf("(%d, %d): R = %d, G = %d, B = %d\n", row, col, (int)imagedata[(row*width + col)*3], (int)imagedata[(row*width + col)*3+1], (int)imagedata[(row*width + col)*3+2]);
      }
  // Use the imagedata array for heights in the terrain!

// GL inits
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH); // Enable Gouraud shading
  glEnable(GL_TEXTURE_2D);
}

void water_timer(int i)
{
	glutTimerFunc(20, water_timer, i);
    glutPostRedisplay();
}

