#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color; 

layout(location = 0) uniform mat4 transform;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;

layout (location = 0) out vec3 ourColor;

void main()
{
  gl_Position = projection * view * transform * vec4(position, 1.0f);
  ourColor = color;
}