#version 460 core

layout (location = 0) in vec3 ourColor;

layout (location = 0) out vec4 color;

void main()
{
	color = vec4(ourColor, 1.0f);
}