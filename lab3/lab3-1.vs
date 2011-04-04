
void main()
{
  gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
 
  vec3 transformedNormal = gl_NormalMatrix * gl_Normal;

  gl_FrontColor = transformedNormal.zzzz;
}
