
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "helpers.h"
#include "readppm.h"
#include "zpr.h"
#include "readjpeg.h"
#include "loadobj.h"



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

  printf("Loading texture %s\n", name);

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

GLdouble* getLightMatrix()
{
  return zprGetLightMatrix();
}

GLdouble* getCameraMatrix()
{
  return zprGetCameraMatrix();
}

Model* loadModel(char* name)
{
  Model* model = 0;
  int nameLen = strlen(name);

  printf("Loading model %s\n", name);

  if (nameLen >= 4 && (!strcmp(name + nameLen - 4, ".obj")
		       || !strcmp(name + nameLen - 4, ".OBJ")))
    {
      model = loadOBJModel(name);
    }
  else
    {
      fprintf(stderr, "Unknown file extension for file %s\n", name);
      fflush(stderr);
    }

  if (!model)
    exit(0);

  printf("Model has vertex colors: %s\n",
	 model->colorArray ? "Yes" : "No");
  printf("Model has vertex normals: %s\n", model->normalArray ? "Yes" : "No");
  printf("Model has texture coordinates: %s\n",
	 model->texCoordArray ? "Yes" : "No");

  return model;
}

void freeModel(Model* model)
{
  if (model)
    {
      if (model->vertexArray)
	free(model->vertexArray);
      if (model->normalArray)
	free(model->normalArray);
      if (model->texCoordArray)
	free(model->texCoordArray);
      if (model->colorArray)
	free(model->colorArray);
      if (model->indexArray)
	free(model->indexArray);
      free(model);
    }
}


static float min(float a, float b)
{
  return (a < b) ? a : b;
}

static float max(float a, float b)
{
  return (a > b) ? a : b;
}

void setModelCenter(Model* model, float x, float y, float z)
{
  const float largeNumber = 1e30;
  float minX = largeNumber;
  float minY = largeNumber;
  float minZ = largeNumber;
  float maxX = -largeNumber;
  float maxY = -largeNumber;
  float maxZ = -largeNumber;
  int i =0;

  for (i = 0; i < model->numVertices; i++)
    {
      minX = min(minX, model->vertexArray[i * 3 + 0]);
      minY = min(minY, model->vertexArray[i * 3 + 1]);
      minZ = min(minZ, model->vertexArray[i * 3 + 2]);
      maxX = max(maxX, model->vertexArray[i * 3 + 0]);
      maxY = max(maxY, model->vertexArray[i * 3 + 1]);
      maxZ = max(maxZ, model->vertexArray[i * 3 + 2]);
    }

  float translationX = -(minX + maxX) / 2 + x;
  float translationY = -(minY + maxY) / 2 + y;
  float translationZ = -(minZ + maxZ) / 2 + z;

  for (i = 0; i < model->numVertices; i++)
    {
      model->vertexArray[i * 3 + 0] += translationX;
      model->vertexArray[i * 3 + 1] += translationY;
      model->vertexArray[i * 3 + 2] += translationZ;
    }
}

void setModelRadius(Model* model, float radius)
{
  float maxSqrDist = 0.f;

  int i =0;

  for (i = 0; i < model->numVertices; i++)
    {
      float sqrDist = model->vertexArray[i * 3 + 0]
	* model->vertexArray[i * 3 + 0]
	+ model->vertexArray[i * 3 + 1]
	* model->vertexArray[i * 3 + 1]
	+ model->vertexArray[i * 3 + 2]
	* model->vertexArray[i * 3 + 2];

      maxSqrDist = max(maxSqrDist, sqrDist);
    }

  if (maxSqrDist < 1e-6)
    return;

  float scale = radius / sqrtf(maxSqrDist);

  for (i = 0; i < model->numVertices; i++)
    {
      model->vertexArray[i * 3 + 0] *= scale;
      model->vertexArray[i * 3 + 1] *= scale;
      model->vertexArray[i * 3 + 2] *= scale;
    }
}

float clamp(float val, float min, float max) {
  float retval = val;
  if (val < min) {
    retval = min;
  } else if (val > max) {
    retval = max;
  }
  return retval;
}

