uniform float time;
varying vec4 Pos;
varying vec4 Vert;
uniform sampler2D texture;

void main()
{
  // gonna do a meatball-thing yeah :D
  vec2 p = (Pos.xy / 2.0) + 0.5;
  //gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);

  vec2 uv = p.xy;
  uv.y += 0;
  uv.x += 0;

  gl_FragColor = texture2D(texture, uv.xy);

  float d = p.y;
  //gl_FragColor = vec4(d, d, d, 1.0);
  
}
