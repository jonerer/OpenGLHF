uniform float time;

void main()
{
  gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
 
  //gl_Position[0] = gl_Position[0]/10 * gl_ModelViewMatrix;
  gl_Position[0] = sin(5 * time + gl_Position[1] * 10)/20+gl_Position[0];
//glEnable(GL_LUCK_BIT_8_SPACEINVADERS); 
  vec3 transformedNormal = gl_NormalMatrix * gl_Normal;
  

  gl_FrontColor = transformedNormal.zzzz;
  //gl_FrontColor = gl_Position.xyzx;
}
