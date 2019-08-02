#version 450 core

uniform vec3 cameraPos;
uniform int someUniform;

void main()
{
    gl_Position = vec4(cameraPos, 1.0f) * vec4(someUniform);
}