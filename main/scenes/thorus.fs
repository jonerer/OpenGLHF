uniform float time;
uniform float timeReaches;
uniform float whiteoutTime;
varying vec4 Pos;
varying vec4 Vert;
uniform sampler2D texture;
uniform sampler2D texture2;
uniform sampler2D texture3;

vec4 screen() {
  float screentime = time + 60.0;
  // this is the "screen"-shader. ctrl-c:d.
  gl_FragColor = gl_Color;
  gl_FragColor.r = clamp(Vert.y + 0.05 * 25.0, 0.0, 25.0);

  //vec2 position = - 1.0 + 2.0 * gl_FragCoord.xy / resolution.xy;
  vec2 position = Pos.xy;
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

  uv.y = (1.0 - (dist - time/4.0 * velocity)) / stretch;
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
  vec2 p2 = (Pos.xy / 2.0) + 0.5;
  vec2 p = Pos.xy;
  //gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);

    // två blobbar!
    vec2 move1;
    move1.x = cos(timeReaches*0.5)*0.5;
    move1.y = sin(timeReaches*1.0)*0.6;
    vec2 move2;
    move2.x = cos(timeReaches*1.3)*0.7;
    move2.y = sin(timeReaches*1.4)*0.8;
    
    float r1 =(dot(p-move1,p-move1))*16.0;
    float r2 =(dot(p+move2,p+move2))*32.0;

    float whiteout = clamp((timeReaches - whiteoutTime) * 2.0 , 1.0, 1000.0);

    // plussa ihop
    float metaball =(whiteout/r1+whiteout/r2);
    float col = clamp(0.0, 1.0, pow(metaball,5.0));
    float hardcol = pow(metaball, 6.5);
    float bgcol = metaball;

    // what uv are we at, bro? (for the border-effect)
    vec2 uv = p2.xy;
    uv -= move1;
    uv -= move2;
    vec3 tcol = texture2D(texture, uv).rgb;

    vec3 bgtex = texture2D(texture3, p).rgb;

    //set the output color
    //vec4 metathing = vec4(tcol * col + hardcol + bgtex * bgcol, 1.0);
    vec4 metathing = vec4(hardcol + bgtex * bgcol, 1.0);

  uv = p2.xy;
  uv.y = uv.y;
  uv.x = uv.x / 2.0 + timeReaches / 140.0;
  
  float fadeTimeFactor = 1.0;
  float fadeStartDelay = 3.0;

  vec2 dist = Pos.xy;
  dist.x /= clamp(pow((timeReaches - fadeStartDelay) / 3.0, 3), 0.0, 100.0) / 5.0;
  dist.y /= clamp(pow((timeReaches - fadeStartDelay) / 3.0, 3), 0.0, 100.0) / 5.0;
  float d = clamp(dot(dist, dist), 0.0, 1.0);
  d = smoothstep(0.0, 1.0, d);
  float d2 = 1.0 - d;

  vec4 bg = texture2D(texture3, uv.xy);
  gl_FragColor = bg*d2 + screenShaderd*d + metathing*d2;
  // gl_FragColor = vec4(d2, d2, d2, 1.0);
  
}
