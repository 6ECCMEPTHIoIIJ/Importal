#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color; 

out vec3 ourColor;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;


void main()
{
  gl_Position = projection * view * transform * vec4(position, 1.0f);
  ourColor = color;
}