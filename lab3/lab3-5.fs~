varying vec3 pixnorm;
varying vec4 pixpos;

void main()
{
  //gl_FragColor = gl_Color;
  float strength = dot(gl_LightSource[0].position.xyz, pixnorm);  
  gl_FragColor = clamp(gl_LightSource[0].diffuse * strength, 0.0, 1.0);

  strength = dot((gl_LightSource[1].position - pixpos).xyz, pixnorm); 
  gl_FragColor += clamp(gl_LightSource[1].diffuse * strength, 0.0, 1.0);

  strength = dot((gl_LightSource[2].position - pixpos).xyz, pixnorm);  
  gl_FragColor += clamp(gl_LightSource[2].diffuse * strength, 0.0, 1.0);

  strength = dot((gl_LightSource[3].position - pixpos).xyz, pixnorm); 
  gl_FragColor += clamp(gl_LightSource[3].diffuse * strength, 0.0, 1.0);
}
