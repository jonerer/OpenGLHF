uniform float time;
varying vec4 Pos;
varying vec4 Vert;

void main()
{
  gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;

  gl_Position = gl_PositionIn[i];
  gl_FrontColor = gl_FrontColorIn[i];
}