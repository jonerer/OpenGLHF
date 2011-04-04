#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>

#include "zpr.h"


#define bool int
#define true 1
#define false 0

static double _left   = 0.0;
static double _right  = 0.0;
static double _bottom = 0.0;
static double _top    = 0.0;

static int  _mouseX      = 0;
static int  _mouseY      = 0;
static bool _mouseLeft   = false;
static bool _mouseMiddle = false;
static bool _mouseRight  = false;

static double _objectMatrix[16];
static double _lightMatrix[16];
static double _cameraMatrix[16];

static void zprReshape(int w,int h);
static void zprMouse(int button, int state, int x, int y);
static void zprMotion(int x, int y);
static void zprKey(unsigned char key, int x, int y);

static float objectPositionX = 0.f;
static float objectPositionY = 0.f;
static float objectPositionZ = -0.5f;
static float objectRotationHeading = 0.f;
static float objectRotationPitch = 0.f;

static float lightRotationHeading = 0.f;
static float lightRotationPitch = 0.f;

static float cameraRotationHeading = 0.f;
static float cameraRotationPitch = 0.f;
static float cameraPositionX = 0.f;
static float cameraPositionY = 0.f;
static float cameraPositionZ = 0.f;

static void updateObjectMatrix()
{
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  glLoadIdentity();
  glTranslatef(objectPositionX, objectPositionY, objectPositionZ);
  glRotatef(objectRotationPitch, 1, 0, 0);
  glRotatef(objectRotationHeading, 0, 1, 0);
  glGetDoublev(GL_MODELVIEW_MATRIX,_objectMatrix);

  glPopMatrix();
  glPopAttrib();
}

static void updateLightMatrix()
{
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  glLoadIdentity();
  glTranslatef(objectPositionX, objectPositionY, objectPositionZ);
  glRotatef(lightRotationPitch, 1, 0, 0);
  glRotatef(lightRotationHeading, 0, 1, 0);
  glGetDoublev(GL_MODELVIEW_MATRIX,_lightMatrix);

  glPopMatrix();
  glPopAttrib();
}

static void updateCameraMatrix()
{
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix(); 

  glLoadIdentity();
  glRotatef(cameraRotationPitch, 1, 0, 0);
  glRotatef(cameraRotationHeading, 0, 1, 0);
  glTranslatef(cameraPositionX, cameraPositionY, cameraPositionZ);
  glGetDoublev(GL_MODELVIEW_MATRIX,_cameraMatrix);

  glPopMatrix();
  glPopAttrib();
}

void
zprInit()
{
  updateObjectMatrix();
  updateLightMatrix();
  updateCameraMatrix();

  glutReshapeFunc(zprReshape);
  glutMouseFunc(zprMouse);
  glutMotionFunc(zprMotion);
  glutKeyboardFunc(zprKey);
}

GLdouble*
zprGetObjectMatrix()
{
  return _objectMatrix;
}

GLdouble*
zprGetLightMatrix()
{
  return _lightMatrix;
}

GLdouble*
zprGetCameraMatrix()
{
  return _cameraMatrix;
}

static void
zprReshape(int w,int h)
{
  _top    =  1.0;
  _bottom = -1.0;
  _left   = -(double)w/(double)h;
  _right  = -_left;
}

static void
zprMouse(int button, int state, int x, int y)
{
  _mouseX = x;
  _mouseY = y;

  if (state==GLUT_UP)
    switch (button)
      {
      case GLUT_LEFT_BUTTON:   _mouseLeft   = false; break;
      case GLUT_MIDDLE_BUTTON: _mouseMiddle = false; break;
      case GLUT_RIGHT_BUTTON:  _mouseRight  = false; break;
      }
  else
    switch (button)
      {
      case GLUT_LEFT_BUTTON:   _mouseLeft   = true; break;
      case GLUT_MIDDLE_BUTTON: _mouseMiddle = true; break;
      case GLUT_RIGHT_BUTTON:  _mouseRight  = true; break;
      }
}

static void
zprKey(unsigned char key, int x, int y)
{
  float speed = 10.f;
  float speedX = 0.f;
  float speedY = 0.f;
  float speedZ = 0.f;

  switch (key)
   {
   case 'w':
     speedZ = 1.f;
     break;
   case 's':
     speedZ = -1.f;
     break;
   case 'q':
     speedY = -1.f;
     break;
   case 'e':
     speedY = 1.f;
     break;
   case 'd':
     speedX = -1.f;
     break;
   case 'a':
     speedX = 1.f;
     break;
   }

  cameraPositionX += _cameraMatrix[0] * speed * speedX;
  cameraPositionY += _cameraMatrix[4] * speed * speedX;
  cameraPositionZ += _cameraMatrix[8] * speed * speedX;
  
  cameraPositionX += _cameraMatrix[1] * speed * speedY;
  cameraPositionY += _cameraMatrix[5] * speed * speedY;
  cameraPositionZ += _cameraMatrix[9] * speed * speedY;

  cameraPositionX += _cameraMatrix[2] * speed * speedZ;
  cameraPositionY += _cameraMatrix[6] * speed * speedZ;
  cameraPositionZ += _cameraMatrix[10] * speed * speedZ;

  updateCameraMatrix();
}

static void
zprMotion(int x, int y)
{
  const int dx = x - _mouseX;
  const int dy = y - _mouseY;

  if (dx==0 && dy==0)
    return;

  bool objectChanged = false;

  if (_mouseRight)
    {
      objectPositionZ += dy * 0.01f;
      objectChanged = true;
    }
  else if (_mouseLeft)
    {
      objectRotationHeading += dx * 0.3f;
      objectRotationPitch += dy * 0.3f;
      objectChanged = true;
    }

  if (objectChanged)
    {
      updateObjectMatrix();
    }

  bool lightChanged = false;

  if (_mouseMiddle)
    {
      lightRotationHeading += dx * 0.3f;
      lightRotationPitch += dy * 0.3f;
      lightChanged = true;
    }

  if (objectChanged || lightChanged)
    {
      updateLightMatrix();
    }


  bool cameraChanged = false;

  if (_mouseMiddle)
    {
      float speed = 0.05f;
      cameraPositionX += _cameraMatrix[0] * speed * -dx;
      cameraPositionY += _cameraMatrix[4] * speed * -dx;
      cameraPositionZ += _cameraMatrix[8] * speed * -dx;

      cameraPositionX += _cameraMatrix[1] * speed * dy;
      cameraPositionY += _cameraMatrix[5] * speed * dy;
      cameraPositionZ += _cameraMatrix[9] * speed * dy;
      cameraChanged = true;
    }
  else if (_mouseRight)
    {
      float speed = 0.05f;
      cameraPositionX += _cameraMatrix[2] * speed * -dy;
      cameraPositionY += _cameraMatrix[6] * speed * -dy;
      cameraPositionZ += _cameraMatrix[10] * speed * -dy;
      cameraChanged = true;
    }
  else if (_mouseLeft)
    {
      cameraRotationHeading += dx * 0.3f;
      cameraRotationPitch += dy * 0.3f;
      cameraChanged = true;
    }

  if (cameraChanged)
    updateCameraMatrix();

  _mouseX = x;
  _mouseY = y;

}
