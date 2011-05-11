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
  vec2 position = Vert;

  vec2 uv;
  float dist = dot(position, position);
  float darkness = smoothstep(0.0, 1.0, dist);

  uv.y = 1 - (dist - time);
  uv.x = position.x / dist;

  float d = dist;
  gl_FragColor = vec4(d, d, d, 1.0);

  gl_FragColor = texture2D(texture, uv)*dist;
}
