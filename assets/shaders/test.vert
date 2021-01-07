#version 410 core

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 lightPos;
uniform vec3 viewPos;

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;

layout (location = 0) out vec3 outLightVector;
layout (location = 1) out vec3 outNormal;
layout (location = 2) out vec3 outViewVector;

void main()
{
   mat4 modelView = view * model;
   vec4 pos = modelView * vec4(inPos, 1.0);

   outViewVector = vec3(modelView * pos);
   outNormal = mat3(inverse(transpose(modelView))) * inNormal;
   vec4 lPos = vec4(lightPos, 1.0) * modelView;
   outLightVector = normalize(lPos.xyz - outViewVector);
   gl_Position = projection * pos;
}
