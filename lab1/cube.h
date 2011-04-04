
#ifndef cube_h
#define cube_h


#include <GL/gl.h>


extern GLfloat cubeVertices[4*6][3];
extern GLfloat cubeNormals[4*6][3];
extern GLfloat cubeColors[4*6][3];
extern GLfloat cubeTexCoords[4*6][2];

extern int numCubeIndices;
extern GLuint cubeIndices[6*6];


#endif
