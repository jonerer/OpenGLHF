varying vec3 pixnorm;
varying vec4 pixmodverpos;
varying vec4 pixpromodverpos;
uniform sampler2D texture;
uniform sampler2D texture2;
varying vec4 pixhax;

void main()
{
  //gl_FragColor = gl_Color;
  float strength = dot(gl_LightSource[0].position.xyz, pixnorm);  
  gl_FragColor = clamp(gl_LightSource[0].diffuse * strength, 0.0, 1.0);

  strength = dot((gl_LightSource[1].position - pixmodverpos).xyz, pixnorm); 
  gl_FragColor += clamp(gl_LightSource[1].diffuse * strength, 0.0, 1.0);

  const vec3 Lm = normalize((gl_LightSource[1].position - pixmodverpos).xyz);
  const vec3 refl = clamp(normalize(2.0*(dot(Lm, pixnorm)) * pixnorm - Lm), 0.0, 1.0);

  strength = pow(dot(refl, vec3(0.0, 0.0, 1.0)), 125.0); 
  gl_FragColor += clamp(gl_LightSource[1].specular * strength, 0.0, 1.0);

  strength = dot((gl_LightSource[2].position - pixmodverpos).xyz, pixnorm);  
  gl_FragColor += clamp(gl_LightSource[2].diffuse * strength, 0.0, 1.0);

  strength = dot((gl_LightSource[3].position - pixmodverpos).xyz, pixnorm); 
  gl_FragColor += clamp(gl_LightSource[3].diffuse * strength, 0.0, 1.0);

  vec4 hax = texture2D(texture, gl_TexCoord[0].xy);
  vec4 hax2 = texture2D(texture2, gl_TexCoord[0].xy);

  float hax_alpha = (pixhax.y + 0.05) * 25;
  hax_alpha = clamp(hax_alpha, -3, 25); // remove for +4 coolness-effect
  hax *= hax_alpha;

  float hax_alpha2 = (-pixhax.y) * 25;
  hax_alpha2 = clamp(hax_alpha2, -3, 25);
  hax2 *= hax_alpha2;

  vec4 new_hax = hax + hax2;

  gl_FragColor *= new_hax;
  // gl_FragColor *= texture2D(texture2, vec2(0,gl_TexCoord[0].y));
}
