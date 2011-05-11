uniform float time;
varying vec4 Pos;
varying vec4 Vert;
uniform sampler2D texture;

void main()
{
  gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
  Pos = gl_Position;
  Vert = gl_Vertex;
}
