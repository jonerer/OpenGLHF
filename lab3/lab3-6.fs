varying vec3 pixnorm;
varying vec4 pixmodverpos;
varying vec4 pixpromodverpos;
varying vec4 vert;

void main()
{
  //gl_FragColor = gl_Color;
  float strength = dot(gl_LightSource[0].position.xyz, pixnorm);  
  gl_FragColor = clamp(gl_LightSource[0].diffuse * strength, 0.0, 1.0);

  strength = dot((gl_LightSource[1].position - pixmodverpos).xyz, pixnorm); 
  gl_FragColor += clamp(gl_LightSource[1].diffuse * strength, 0.0, 1.0);



  const vec3 Lm = normalize((gl_LightSource[1].position - pixmodverpos).xyz);
  //const vec3 refl = clamp(normalize(2.0*(dot(Lm, pixnorm)) * pixnorm - Lm), 0.0, 1.0);
  const vec3 refl = normalize(2.0*(dot(Lm, pixnorm)) * pixnorm - Lm);
  	
  //strength = pow(dot(refl, vec3(0.0, 0.0, 1.0)), 125); 


  strength = pow(dot(refl, normalize(-pixmodverpos.xyz)), 125.0);
  if (strength > 0)
    gl_FragColor += gl_LightSource[1].specular * strength;

  strength = dot((gl_LightSource[2].position - pixmodverpos).xyz, pixnorm);  
  gl_FragColor += clamp(gl_LightSource[2].diffuse * strength, 0.0, 1.0);

  strength = dot((gl_LightSource[3].position - pixmodverpos).xyz, pixnorm); 
  gl_FragColor += clamp(gl_LightSource[3].diffuse * strength, 0.0, 1.0);
}
