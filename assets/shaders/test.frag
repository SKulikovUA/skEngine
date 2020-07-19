#version 450 core

layout (location = 0) in vec3 inLightVec;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec3 inViewVector;

layout (location = 0) out vec4 outColor;

void main()
{
   vec3 Eye = normalize(inViewVector);
   vec3 Reflected = normalize(reflect(inLightVec, inNormal)); 
 
   vec4 IAmbient = vec4(0.2, 0.2, 0.2, 1.0);
   vec4 IDiffuse = vec4(0.5, 0.5, 0.5, 0.5) * max(dot(inNormal, inLightVec), 0.0);
   float specular = 0.8;
   vec4 ISpecular = vec4(0.5, 0.5, 0.5, 1.0) * pow(max(dot(Reflected, Eye), 0.0), 0.8) * specular; 
   
   vec3 inColor = vec3(0.2, 0.2, 0.2);
   outColor = vec4((IAmbient + IDiffuse) * vec4(inColor, 1.0) + ISpecular);
}
