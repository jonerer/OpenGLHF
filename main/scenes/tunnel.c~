
#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265
GLuint tunnelTexture;

unsigned char *imagedata;
int height, width;
float camera_z = 0;

#include "../helpers.h"

int maxaddr = 0;
int timeStarted = 0;

float myElapsedTime() {
  return getElapsedTime() - timeStarted;
}

void tunnel_init()
{
  timeStarted = getElapsedTime();
	tunnelTexture = loadTexture("textures/illusion.jpg");
  // Place one-time initialization code here
}

void tunnel_load() {
  printf("%s", "yeah");
  imagedata = readppm("heightmaps/fft-terrain-360-bred.ppm", &height, &width);
  //imagedata = readppm("heightmaps/fft-terrain.ppm", &height, &width);
}


int heightAt(int row, int col) {
  //printf("%d\n", col);
  int addr = ((row % height)*width + col)*3;
  if (addr > maxaddr) {
    maxaddr = addr;
    //printf("new maxaddr: %d", maxaddr);
  }
  return (int)imagedata[(row*width + col)*3];
}

void tunnel_disp()
{
  // This function is called whenever it is time to render
  //  a new frame; due to the idle()-function below, this
  //  function will get called several times per second

  // Clear framebuffer & zbuffer
  glClearColor(0.3, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90, 1, 0.01, 200);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
  glEnable(GL_TEXTURE_2D);
  
  //glLoadMatrixd(getObjectMatrix());
  //glLoadMatrixd(getCameraMatrix());
  //printf(" %i \n", getElapsedTime());
  //printf(" %i \n", getElapsedTime());
  //printf(" %i \n", 20*getElapsedTime());
  float sec = myElapsedTime()*20;
  float xsinfreq = 0.02;
  float ysinfreq = 0.04;
  camera_z = sec;
  //printf(" %i \n", getElapsedTime());
  //printf(" %f \n", sec);
  //gluLookAt(cos(sec * xsinfreq) * 5, sin(sec * ysinfreq)*5, - sec, 0,0, -10 - sec, 0, 1, 0);
  //printf("%f\n", center_x);
  gluLookAt(0, 0, - sec, 0, 0, -10 - sec, 0, 1, 0);
  // Enable Gouraud shading
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  // Draw polygon
  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);


float depth = -5;
int z = 1;
float zstep = 1;
float ztexstep = 0.03;
//float hyp = 5;
float textint = 0;
glBindTexture(GL_TEXTURE_2D, tunnelTexture);
float curvature = 0.01;
double curr_curv = 0;
float z_from_camera = 0;

float ztexphase = 0;
glRotatef(myElapsedTime()*5, 0, 0, 1);
  //printf(" %i \n", getElapsedTime());
for (;z <= camera_z + 200; z++) {
  //printf("%d - %d - %d \n", z, camera_z, getElapsedTime());
  //printf("%s", "disp\n");

  double curvnext = curr_curv;
  z_from_camera = z*zstep - camera_z;
  curvnext = curr_curv + (curvature * z_from_camera);
  int i = 1;
  if (z*zstep >= camera_z) {
    for(;i <= 360; i++) {
	//printf("fiskapa %d - ", z);
	//printf("%d", i);
	//printf("\n");
	float heightDivisorer = 30;
	float baseHyp = 20;
	float hyp =  baseHyp + heightAt(z, i) / heightDivisorer;
	float hypC = baseHyp + heightAt(z, i+1) / heightDivisorer;
	float hypR = baseHyp + heightAt(z+1, i) / heightDivisorer;
	float hypCR = baseHyp + heightAt(z+1, i+1) / heightDivisorer;
        //hyp = hypC = hypR = hypCR = 5;
	//printf("%f\n", hyp);

	float x = cos(i*PI/180.0);
	float y = sin(i*PI/180.0);
	float xplusone = cos((i+1)*PI/180.0);
	float yplusone = sin((i+1)*PI/180.0);


  	  glBegin(GL_POLYGON);
          glTexCoord2f(ztexphase, textint);
	  glVertex3f(x*hyp + curr_curv, y*hyp, -z*zstep);

          glTexCoord2f(ztexphase+ztexstep, textint);	
	  glVertex3f(x*hypR + curvnext, y*hypR, -(z*zstep + zstep));

          glTexCoord2f(ztexphase+ztexstep, textint+10/360);
	  glVertex3f(xplusone*hypCR + curvnext, yplusone*hypCR, -(z*zstep + zstep));

          glTexCoord2f(ztexphase, textint+10/360);
	  glVertex3f(xplusone*hypC + curr_curv, yplusone*hypC, -z*zstep);
  	  glEnd();
    }
  }
  textint = (textint+10/360);
  ztexphase += ztexstep;
  if (z_from_camera > 0) {
    curr_curv = curvnext;
  }

}

  // Swap front- and backbuffers
  glutSwapBuffers();
}


