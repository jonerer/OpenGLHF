
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "helpers.h"
#include "readppm.h"
#include "zpr.h"
#include "readjpeg.h"



static double startTime = 0;

void resetElapsedTime()
{
  struct timeval timeVal;
  gettimeofday(&timeVal, 0);
  startTime = (double) timeVal.tv_sec + (double) timeVal.tv_usec * 0.000001;
}

void initHelperLibrary()
{
  resetElapsedTime();

  zprInit();
}


float getElapsedTime()
{
  struct timeval timeVal;
  gettimeofday(&timeVal, 0);
  double currentTime = (double) timeVal.tv_sec
    + (double) timeVal.tv_usec * 0.000001;

  return currentTime - startTime;
}


GLuint loadTexture(char* name)
{
  GLuint texNum;
  int width = 0, height = 0;
  char* pixelData = 0;
  int nameLen = strlen(name);

  if ((nameLen >= 4 && (!strcmp(name + nameLen - 4, ".jpg")
			|| !strcmp(name + nameLen - 4, ".JPG")))
      || (nameLen >= 5 && (!strcmp(name + nameLen - 5, ".jpeg")
			   || !strcmp(name + nameLen - 5, ".JPEG"))))
    {
      read_JPEG_file(name, &pixelData, &width, &height);
    }
  else if (nameLen >= 4 && (!strcmp(name + nameLen - 4, ".ppm")
			    || !strcmp(name + nameLen - 4, ".PPM")))
    {
      pixelData = readppm(name, &width, &height);
    }

  if (!pixelData)
    exit(0);

  glGenTextures(1, &texNum);
  glBindTexture(GL_TEXTURE_2D, texNum);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0,
	       GL_RGB, GL_UNSIGNED_BYTE, pixelData);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  free(pixelData);

  return texNum;
}

GLdouble* getObjectMatrix()
{
  return zprGetObjectMatrix();
}
