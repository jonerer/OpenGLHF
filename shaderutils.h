
#ifndef shaderutils_h
#define shaderutils_h

// Load a shader from file, and creates a shader object
// Specify GL_VERTEX_SHADER or GL_FRAGMENT_SHADER depending on
//  shader type
// Returns an identifier for the shader, or 0 on error
GLuint createShaderFromFile(GLuint shaderType, char* fileName);

// Given a vertex shader and a fragment shader, creates a shader program
// Returns an identifier for the program, or 0 on error
GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader);

// Given a shader program and a uniform variable name, returns an identifier
//  for the variable's location; the variable can later on be written
//  to using glUniform*() 
// Returns an identifier for the variable's location, or -1 if not found
GLint getUniformLocation(GLuint program, char* variableName);


#endif
