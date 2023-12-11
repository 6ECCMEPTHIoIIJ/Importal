#version 460 core

layout (location = 0) in vec3 ourColor;
layout (location = 1) in vec2 v_textureCoords;

layout (location = 0) out vec4 color;

layout (location = 4) uniform sampler2D u_Texture;

void main()
{
	vec4 textureColor = texture2D(u_Texture, v_textureCoords);
	color = textureColor;
}