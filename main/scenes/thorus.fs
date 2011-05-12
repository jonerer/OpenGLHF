uniform float time;
uniform float timeReaches;
varying vec4 Pos;
varying vec4 Vert;
uniform sampler2D texture;
uniform sampler2D texture2;
uniform sampler2D texture3;

vec4 screen() {
  float screentime = time + 60;
  // this is the "screen"-shader. ctrl-c:d.
  gl_FragColor = gl_Color;
  gl_FragColor.r = clamp(Vert.y + 0.05 * 25.0, 0.0, 25.0);

  //vec2 position = - 1.0 + 2.0 * gl_FragCoord.xy / resolution.xy;
  vec2 position = Pos;
  bool y_shear = screentime > 15.0;
  bool x_shear = screentime > 20.0;
  bool has_velocity = screentime > 3.0;

  float velocity = 0.0;
  if (has_velocity) 
    velocity = clamp((screentime - 3.0) / 5.0, 0.0, 2.0);
  if (y_shear)
    position.y += sin(screentime - 15.0) / 3.0;

  vec2 uv;
  float dist = abs(position.y);
  float darkness = pow(dist, clamp(velocity, 0.0, 1.0));
  float stretch = 3.0;

  uv.y = (1 - (dist - time/4.0 * velocity)) / stretch;
  uv.x = position.x / pow(dist, velocity) / stretch;

  if (x_shear) {
    uv.x += sin(time - 20.0);
  }

  if (position.y > 0.0) {
    uv.x += 0.5;
  }


  float d = time;
  gl_FragColor = vec4(d, d, d, 1.0);

  return texture2D(texture2, uv)*darkness;

}

void main()
{
  vec4 screenShaderd = screen();
    // gl_FragColor = screenShaderd;


  // gonna do a meatball-thing yeah :D
  vec2 p = (Pos.xy / 2.0) + 0.5;
  //gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);

  vec2 uv = p.xy;
  uv.y = uv.y;
  uv.x = uv.x / 2.0;

  vec2 dist = Pos.xy;
  dist.x /= clamp(timeReaches - 3.0, 0.0, 100.0) / 5.0;
  dist.y /= clamp(timeReaches - 3.0, 0.0, 100.0) / 5.0;
  float d = clamp(dot(dist, dist), 0.0, 1.0);
  d = smoothstep(0.0, 1.0, d);
  float d2 = 1 - d;

  vec4 bg = texture2D(texture3, uv.xy);
  gl_FragColor = bg*d2 + screenShaderd*d;
  // gl_FragColor = vec4(d2, d2, d2, 1.0);
  
}
