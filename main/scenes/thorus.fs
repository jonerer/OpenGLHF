uniform float time;
varying vec4 Pos;
varying vec4 Vert;
uniform sampler2D texture;

void main()
{
  
  vec3 p = Vert;
  float strength = p.z + time*30;
  gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);

  strength = clamp(strength, 1.0, 50.0);
  strength = smoothstep(1.0, 50.0, strength);

  gl_FragColor = texture2D(texture, p.xy)*strength + vec4(0.0, 0.0, 0.3, 1);

  float d = time;
  //gl_FragColor = vec4(d, d, d, 1.0);
}
