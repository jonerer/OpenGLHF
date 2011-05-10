

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

#ifndef GL_VERSION_2_0
#error This program needs OpenGL 2.0 libraries to compile
#endif

#include "../helpers.h"
#include "../shaderutils.h"


Model* screen_model = 0;

GLuint screen_shaderProgram = 0;
int shaderTimeLocation;


#define NUM_SCREEN_LIGHTS 4

typedef struct
{
  int enabled;
  GLfloat position[4];
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
} LightInfo;

LightInfo screen_lights[NUM_SCREEN_LIGHTS] =
  {
    { // Light 0
      1,                      // Disabled/Enabled
      { 0.1, 0.03, 1.0, 0.0 }, // gl_LightSource[0].position
      { 0.0, 0.0, 0.0, 0.0 }, // gl_LightSource[0].ambient
      { 0.5, 0.5, 0.5, 0.0 }, // gl_LightSource[0].diffuse
      { 0.0, 0.0, 0.0, 0.0 }, // gl_LightSource[0].specular
    },

    { // Light 1
      0,                      // Disabled/Enabled
      { 1.0, 0.0,-1.0, 1.0 }, // gl_LightSource[1].position
      { 0.0, 0.0, 0.0, 0.0 }, // gl_LightSource[1].ambient
      { 0.7, 0.0, 0.0, 0.0 }, // gl_LightSource[1].diffuse
      { 1.0, 1.0, 1.0, 0.0 }, // gl_LightSource[1].specular
    },

    { // Light 2
      0,                      // Disabled/Enabled
      { 1.0, 1.0, 0.0, 1.0 }, // gl_LightSource[2].position
      { 0.0, 0.0, 0.0, 0.0 }, // gl_LightSource[2].ambient
      { 0.0, 0.7, 0.0, 0.0 }, // gl_LightSource[2].diffuse
      { 0.0, 0.0, 0.0, 0.0 }, // gl_LightSource[2].specular
    },

    { // Light 3
      0,                      // Disabled/Enabled
      { 1.0, 0.0,-3.0, 1.0 }, // gl_LightSource[3].position
      { 0.0, 0.0, 0.0, 0.0 }, // gl_LightSource[3].ambient
      { 0.0, 0.0, 0.7, 0.0 }, // gl_LightSource[3].diffuse
      { 0.0, 0.0, 0.0, 0.0 }, // gl_LightSource[3].specular
    },
  };


void screen_init()
{
  // Place one-time initialization code here
  initHelperLibrary();
  // load model
  screen_model = loadModel("../models/various/teapot.obj");
  setModelCenter(screen_model, 0.f, 0.f, 0.f);
  setModelRadius(screen_model, 0.3f);

  // Create vertex shader
  GLuint vertexShader = createShaderFromFile(GL_VERTEX_SHADER, "scenes/screen.vs");
  if (!vertexShader)
    printf("couldn't create shader program!");

  // Create fragment shader
  GLuint fragmentShader = createShaderFromFile(GL_FRAGMENT_SHADER, "scenes/screen.fs");
  if (!fragmentShader)
    printf("couldn't create shader program!");

  // Create shader program
  screen_shaderProgram = createShaderProgram(vertexShader, fragmentShader);
  if (!screen_shaderProgram)
    printf("couldn't create shader program!");

  shaderTimeLocation = getUniformLocation(screen_shaderProgram, "time");
}

void screen_load() {
  printf("whaaaa\n");
}

void screen_setLightSources()
{
  // Feed lightsource settings into OpenGL; when writing shader
  //  code, this data can be read from the gl_LightSource[i] structures

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  int light;
  for (light = 0; light < NUM_SCREEN_LIGHTS; light++)
    {
      if (screen_lights[light].enabled)
	{
	  // Lightsource is enabled; set parameters using
	  //  the current light-matrix

	  glLoadMatrixd(getLightMatrix());
	  glLightfv(GL_LIGHT0 + light, GL_POSITION, screen_lights[light].position);
	  glLightfv(GL_LIGHT0 + light, GL_AMBIENT, screen_lights[light].ambient);
	  glLightfv(GL_LIGHT0 + light, GL_DIFFUSE, screen_lights[light].diffuse);
	  glLightfv(GL_LIGHT0 + light, GL_SPECULAR, screen_lights[light].specular);
	}
      else
	{
	  // Lightsource is disabled; set all parameters to zero

	  GLfloat zero[4] = { 0.0 };
	  glLoadIdentity();
	  glLightfv(GL_LIGHT0 + light, GL_POSITION, zero);
	  glLightfv(GL_LIGHT0 + light, GL_AMBIENT, zero);
	  glLightfv(GL_LIGHT0 + light, GL_DIFFUSE, zero);
	  glLightfv(GL_LIGHT0 + light, GL_SPECULAR, zero);
	}
    }

  glPopMatrix();
}

void screen_renderLightSources()
{
  // Display location and color of all enabled lightsources

  glPushAttrib(GL_ALL_ATTRIB_BITS);

  glMatrixMode(GL_MODELVIEW);

  glPushMatrix();
  glLoadMatrixd(getLightMatrix());

  int light;
  for (light = 0; light < NUM_SCREEN_LIGHTS; light++)
    {
      if (screen_lights[light].enabled)
	{
	  // If directional light, draw line from origin of object
	  //  in the direction of the light
	  // If positional light, draw line from origin of object
	  //  to location of light

	  glBegin(GL_LINES);
	  glColor3f(screen_lights[light].diffuse[0],
		    screen_lights[light].diffuse[1],
		    screen_lights[light].diffuse[2]);
	  glVertex3f(0, 0, 0);
	  glVertex3f(screen_lights[light].position[0],
		     screen_lights[light].position[1],
		     screen_lights[light].position[2]);
	  glEnd();

	  // If positional light, draw a sphere at the location 
	  //  of the light
	  if (screen_lights[light].position[3] != 0.f)
	    {
	      glPushMatrix();
	      glTranslatef(screen_lights[light].position[0],
			   screen_lights[light].position[1],
			   screen_lights[light].position[2]);
	      glutSolidSphere(0.1f, 10, 10);
	      glPopMatrix();
	    }
	  
	}
    }

  glPopMatrix();
  glPopAttrib();
}

void screen_disp()
{
  // This function is called whenever it is time to render
  //  a new frame; due to the idle()-function below, this
  //  function will get called several times per second

  // Clear framebuffer & zbuffer
  glClearColor(0.3, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // Position lights
  screen_setLightSources();

  // Setup projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90, 1, 0.01, 100);

  // Setup object matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMultMatrixd(getObjectMatrix());

  // Enable Z-buffering
  glEnable(GL_DEPTH_TEST);

  // Enable backface culling
  glDisable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);

  // Activate shader program
  glUseProgram(screen_shaderProgram);
  glUniform1f(shaderTimeLocation, getElapsedTime());
	//printf("%f", getElapsedTime());
  
  // Draw mesh using array-based API
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, screen_model->vertexArray);
  glNormalPointer(GL_FLOAT, 0, screen_model->normalArray);
  glTexCoordPointer(2, GL_FLOAT, 0, screen_model->texCoordArray);
  glDrawElements(GL_TRIANGLES, screen_model->numIndices, GL_UNSIGNED_INT,
		 screen_model->indexArray);

  // Deactivate shader program
  glUseProgram(0);

  glPopClientAttrib();
  glPopAttrib();

  screen_renderLightSources();

  // Swap front- and backbuffers
  glutSwapBuffers();
}




