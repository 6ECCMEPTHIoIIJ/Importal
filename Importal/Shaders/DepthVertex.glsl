#version 460 core

layout (location = 0) in  vec4 position;

layout (location = 0) uniform mat4 projectionLight;
layout (location = 1) uniform mat4 shadowLight;
layout (location = 2) uniform mat4 transform;

out vec4 v_position;

void main(void)
{
    v_position = projectionLight * shadowLight * transform * position;
    gl_Position = v_position;
}
