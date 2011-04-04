
#include <stdio.h>
#include <stdlib.h>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

#ifndef GL_VERSION_2_0
#error This program needs OpenGL 2.0 libraries to compile
#endif

#include "shaderutils.h"


GLuint createShaderFromFile(GLenum shaderType, char* fileName)
{
  printf("Loading shader file %s\n", fileName);

  // Create shader object
  GLuint shader = glCreateShader(shaderType);
  if (!shader || glGetError() != GL_NO_ERROR)
    {
      fprintf(stderr, "Error: Unable to create shader object\n");
      return 0;
    }

  // Load source file from disk
  FILE* f = fopen(fileName, "rt");
  if (!f)
    {
      fprintf(stderr, "Error: Unable to open file %s\n", fileName);
      return 0;
    }

  fseek(f, 0, SEEK_END);
  int length = ftell(f);
  fseek(f, 0, SEEK_SET);
  char* buffer = malloc(length + 1);
  fread(buffer, 1, length, f);
  fclose(f);
  buffer[length] = '\0';
  const GLchar* strings[] = { buffer };

  // Feed source code into shader object
  glShaderSource(shader, 1, strings, NULL);

  free(buffer);

  // Compile shader
  printf("Compiling shader...\n");
  glCompileShader(shader);

  // If compilation produced any messages, print them
  GLchar log[16384];
  GLsizei logLength;
  glGetShaderInfoLog(shader, sizeof(log) - 1, &logLength, log);
  if (logLength)
    {
      printf("%s", log);
    }

  // Check if compilation was successful
  GLint compileStatus;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
  if (compileStatus != GL_TRUE)
    {
      fprintf(stderr, "Error: Shader compilation failed!\n");
      return 0;
    }
  else
    printf("Done.\n");

  return shader;
}

GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
  printf("Creating shader program...\n");

  // Create a shader program; attach vertex and fragment shaders,
  // and link
  GLuint shaderProgram = glCreateProgram();
  if (!shaderProgram)
    {
      fprintf(stderr, "Error: Unable to create shader program\n");
      return 0;
    }

  glAttachShader(shaderProgram, vertexShader);
  if (glGetError() != GL_NO_ERROR)
    {
      fprintf(stderr, "Error: Unable to attach vertex shader to program\n");
      return 0;
    }
  glAttachShader(shaderProgram, fragmentShader);
  if (glGetError() != GL_NO_ERROR)
    {
      fprintf(stderr, "Error: Unable to attach fragment shader to program\n");
      return 0;
    }
  glLinkProgram(shaderProgram);
  if (glGetError() != GL_NO_ERROR)
    {
      fprintf(stderr, "Error: Unable to link shader program");
      return 0;
    }

  // If linking produced any messages, print them
  GLchar log[16384];
  GLsizei logLength;
  glGetProgramInfoLog(shaderProgram, sizeof(log) - 1, &logLength, log);
  if (logLength)
    {
      printf("%s", log);
    }

  // Check if linking was successful
  GLint linkStatus;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);
  if (linkStatus != GL_TRUE)
    {
      fprintf(stderr, "Error: Shader program linking failed!\n");
      return 0;
    }
  else
    printf("Done.\n");

  return shaderProgram;
}

GLint getUniformLocation(GLuint program, char* variableName)
{
  // Locate uniform variable in shader program
  GLint location = glGetUniformLocation(program, variableName);
  if (location != -1 && glGetError() == GL_NO_ERROR)
    return location;
  else
    {
      printf("Warning: Uniform variable \"%s\" not found in shader program\n",
	     variableName);
      return -1;
    }
}
