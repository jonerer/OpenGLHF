uniform float time;
uniform vec2 resolution;
uniform sampler2D texture;
uniform sampler2D texture2;
varying vec4 Pos;
varying vec4 Vert;

void main()
{
  gl_FragColor = gl_Color;
  gl_FragColor.r = clamp(Vert.y + 0.05 * 25.0, 0.0, 25.0);

  //vec2 position = - 1.0 + 2.0 * gl_FragCoord.xy / resolution.xy;
  vec2 position = Pos;
  bool y_shear = time > 15.0;
  bool x_shear = time > 20.0;
  bool has_velocity = time > 3.0;

  float velocity = 0.0;
  if (has_velocity) 
    velocity = clamp((time - 3.0) / 5.0, 0.0, 2.0);
  if (y_shear)
    position.y += sin(time - 15.0) / 3.0;

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

  gl_FragColor = texture2D(texture2, uv)*darkness;
  
}
