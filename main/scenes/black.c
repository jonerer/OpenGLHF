

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


Model* model = 0;

GLuint shaderProgram = 0;
int shaderTimeLocation;


#define NUM_LIGHTS 4

typedef struct
{
  int enabled;
  GLfloat position[4];
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
} LightInfo;

LightInfo lights[NUM_LIGHTS] =
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


void black_init()
{
  // Place one-time initialization code here
  initHelperLibrary();
  // load model
  model = loadModel("../models/various/teapot.obj");
  setModelCenter(model, 0.f, 0.f, 0.f);
  setModelRadius(model, 0.3f);

  // Create vertex shader
  GLuint vertexShader = createShaderFromFile(GL_VERTEX_SHADER, "scenes/black.vs");
  if (!vertexShader)
    printf("couldn't create shader program!");

  // Create fragment shader
  GLuint fragmentShader = createShaderFromFile(GL_FRAGMENT_SHADER, "scenes/black.fs");
  if (!fragmentShader)
    printf("couldn't create shader program!");

  // Create shader program
  shaderProgram = createShaderProgram(vertexShader, fragmentShader);
  if (!shaderProgram)
    printf("couldn't create shader program!");

  shaderTimeLocation = getUniformLocation(shaderProgram, "time");
}

void black_load() {

}

void setLightSources()
{
  // Feed lightsource settings into OpenGL; when writing shader
  //  code, this data can be read from the gl_LightSource[i] structures

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  int light;
  for (light = 0; light < NUM_LIGHTS; light++)
    {
      if (lights[light].enabled)
	{
	  // Lightsource is enabled; set parameters using
	  //  the current light-matrix

	  glLoadMatrixd(getLightMatrix());
	  glLightfv(GL_LIGHT0 + light, GL_POSITION, lights[light].position);
	  glLightfv(GL_LIGHT0 + light, GL_AMBIENT, lights[light].ambient);
	  glLightfv(GL_LIGHT0 + light, GL_DIFFUSE, lights[light].diffuse);
	  glLightfv(GL_LIGHT0 + light, GL_SPECULAR, lights[light].specular);
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

void renderLightSources()
{
  // Display location and color of all enabled lightsources

  glPushAttrib(GL_ALL_ATTRIB_BITS);

  glMatrixMode(GL_MODELVIEW);

  glPushMatrix();
  glLoadMatrixd(getLightMatrix());

  int light;
  for (light = 0; light < NUM_LIGHTS; light++)
    {
      if (lights[light].enabled)
	{
	  // If directional light, draw line from origin of object
	  //  in the direction of the light
	  // If positional light, draw line from origin of object
	  //  to location of light

	  glBegin(GL_LINES);
	  glColor3f(lights[light].diffuse[0],
		    lights[light].diffuse[1],
		    lights[light].diffuse[2]);
	  glVertex3f(0, 0, 0);
	  glVertex3f(lights[light].position[0],
		     lights[light].position[1],
		     lights[light].position[2]);
	  glEnd();

	  // If positional light, draw a sphere at the location 
	  //  of the light
	  if (lights[light].position[3] != 0.f)
	    {
	      glPushMatrix();
	      glTranslatef(lights[light].position[0],
			   lights[light].position[1],
			   lights[light].position[2]);
	      glutSolidSphere(0.1f, 10, 10);
	      glPopMatrix();
	    }
	  
	}
    }

  glPopMatrix();
  glPopAttrib();
}

void black_disp()
{
  // This function is called whenever it is time to render
  //  a new frame; due to the idle()-function below, this
  //  function will get called several times per second

  // Clear framebuffer & zbuffer
  glClearColor(0.3, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // Position lights
  setLightSources();

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
  glUseProgram(shaderProgram);
  glUniform1f(shaderTimeLocation, getElapsedTime());
	//printf("%f", getElapsedTime());
  
  // Draw mesh using array-based API
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, model->vertexArray);
  glNormalPointer(GL_FLOAT, 0, model->normalArray);
  glTexCoordPointer(2, GL_FLOAT, 0, model->texCoordArray);
  glDrawElements(GL_TRIANGLES, model->numIndices, GL_UNSIGNED_INT,
		 model->indexArray);

  // Deactivate shader program
  glUseProgram(0);

  glPopClientAttrib();
  glPopAttrib();

  renderLightSources();

  // Swap front- and backbuffers
  glutSwapBuffers();
}

void functionKeys(int key, int mouseX, int mouseY)
{
  // Listen for function-keys, and enable/disable corresponding 
  //  lightsources when they are pressed
  switch (key)
    {
    case GLUT_KEY_F1: lights[0].enabled = 1 - lights[0].enabled; break;
    case GLUT_KEY_F2: lights[1].enabled = 1 - lights[1].enabled; break;
    case GLUT_KEY_F3: lights[2].enabled = 1 - lights[2].enabled; break;
    case GLUT_KEY_F4: lights[3].enabled = 1 - lights[3].enabled; break;
    }
}


