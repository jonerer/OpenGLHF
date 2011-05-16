uniform float time;
varying vec4 Pos;
varying vec4 Vert;
uniform sampler2D texture;

void main()
{
  
  vec3 p = Vert.xyz;
  float strength = clamp(p.z, -180.0, 0.0) + clamp(time*30.0, 0.0, 180.0);
  gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);

  strength = clamp(strength, 1.0, 50.0);
  strength = smoothstep(1.0, 50.0, strength);

  gl_FragColor = texture2D(texture, p.xy)*strength + vec4(0.0, 0.0, 0.3, 1);

  float d = time;
  //gl_FragColor = vec4(d, d, d, 1.0);
}
