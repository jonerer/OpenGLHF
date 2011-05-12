uniform float time;
uniform float timeReaches;
varying vec4 Pos;
varying vec4 Vert;
uniform sampler2D texture;
uniform sampler2D texture2;

void main()
{
  gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
  Pos = gl_Position;
  Vert = gl_Vertex;
}
