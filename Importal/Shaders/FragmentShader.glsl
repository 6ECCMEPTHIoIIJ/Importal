#version 460 core

layout (location = 0) in vec3 ourColor;
layout (location = 1) in vec2 v_textureCoords;

layout (location = 0) out vec4 color;

layout (location = 3) uniform sampler2D u_Texture;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

void main()
{
	vec4 textureColor = texture2D(texture_diffuse1, v_textureCoords);
	color = textureColor;
}