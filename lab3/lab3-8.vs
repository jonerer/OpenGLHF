uniform float time;
varying vec3 pixnorm;
varying vec4 pixmodverpos;
varying vec4 pixpromodverpos;
varying vec4 pixhax;


void main()
{
  gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
  pixmodverpos = gl_ModelViewMatrix*gl_Vertex;

  pixhax = gl_Vertex;
  pixpromodverpos = gl_Position;

  vec3 transformedNormal = gl_NormalMatrix * gl_Normal;

  pixnorm = normalize(transformedNormal);
  gl_TexCoord[0] = gl_MultiTexCoord0;
}
