#version 410 core

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 lightPos;
uniform vec3 viewPos;

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;


out VS_OUT
{
  vec3 lightVector;
  vec3 normal;
  vec3 viewVector;
}vs_out;

void main()
{
   mat4 modelView = view * model;
   vec4 pos = modelView * vec4(inPos, 1.0);

   vs_out.viewVector = vec3(modelView * pos);
   mat3 normalMatrix = transpose(inverse(mat3(modelView)));
   vs_out.normal = normalize(normalMatrix * inNormal);
   vec4 lPos = modelView * vec4(lightPos, 1.0);
   vs_out.lightVector = normalize(lPos.xyz - vs_out.viewVector);
   gl_Position = projection * pos;
}
