//#version 460 core
//
//layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 normal; 
//layout (location = 2) in vec2 textureCoords; 
//layout (location = 3) in vec3 tangent;
//layout (location = 4) in vec3 bitangent;
//
//layout (location = 0) uniform mat4 transform;
//layout (location = 1) uniform mat4 view;
//layout (location = 2) uniform mat4 projection;
//
//layout (location = 1) out vec2 v_textureCoords;
//
//out vec2 uv;
//out mat3 tbnMatrix_viewSpace;
//out vec4 fragmentPosition_viewSpace;
//out vec4 fragmentPosition_worldSpace;
//out vec3 fragmentNormal;
//
//void main()
//{
//  vec4 vertexPosition_worldSpace = transform * vec4(position, 1.0f);
//  vec4 vertexPosition_viewSpace = view * vertexPosition_worldSpace;
//  gl_Position = projection * vertexPosition_viewSpace;
//
//  fragmentPosition_viewSpace = vertexPosition_viewSpace;
//  fragmentPosition_worldSpace = vertexPosition_worldSpace;
//  uv = textureCoords;
//  fragmentNormal = normal;
//
//  mat3 modelViewMatrix_3x3 = mat3(view * transform);
//  vec3 vertexTangent = normalize(tangent);
//  vec3 vertexBiTangent = normalize(bitangent);
//  vec3 vertexNormal = normalize(normal);
//
//  tbnMatrix_viewSpace = modelViewMatrix_3x3 * mat3(
//    vertexTangent,
//    vertexBiTangent,
//    vertexNormal
//  );
//}
//
#version 460 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textCoord;

layout (location = 0) uniform mat4 transform;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 projection;

layout (location = 3) uniform mat4 lightProjection;
layout (location = 4) uniform mat4 shadowLight;
layout (location = 5) uniform vec4 u_lightDirection;

out vec4 v_position;
out vec2 v_textCoord;
out vec3 v_normal;
out vec4 v_positionLightMatrix;
out mat4 v_viewMatrix;

void main(void)
{
    mat4 viewTransform = view * transform;

    gl_Position = projection * viewTransform * position;

    v_textCoord = textCoord;
    v_normal = normalize(vec3(viewTransform * vec4(normal, 0.f)));
    v_position = viewTransform * position;

    v_positionLightMatrix = lightProjection * shadowLight * transform * position;
    v_viewMatrix = view;
}
