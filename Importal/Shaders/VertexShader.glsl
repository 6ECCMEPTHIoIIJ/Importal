#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal; 
layout (location = 2) in vec2 textureCoords; 
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

layout (location = 0) uniform mat4 transform;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 projection;

layout (location = 1) out vec2 v_textureCoords;

out vec2 uv;
out mat3 tbnMatrix_viewSpace;
out vec4 fragmentPosition_viewSpace;
out vec4 fragmentPosition_worldSpace;
out vec3 fragmentNormal;

void main()
{
  vec4 vertexPosition_worldSpace = transform * vec4(position, 1.0f);
  vec4 vertexPosition_viewSpace = view * vertexPosition_worldSpace;
  gl_Position = projection * vertexPosition_viewSpace;

  fragmentPosition_viewSpace = vertexPosition_viewSpace;
  fragmentPosition_worldSpace = vertexPosition_worldSpace;
  uv = textureCoords;
  fragmentNormal = normal;

  mat3 modelViewMatrix_3x3 = mat3(view * transform);
  vec3 vertexTangent = normalize(tangent);
  vec3 vertexBiTangent = normalize(bitangent);
  vec3 vertexNormal = normalize(normal);

  tbnMatrix_viewSpace = modelViewMatrix_3x3 * mat3(
    vertexTangent,
    vertexBiTangent,
    vertexNormal
  );
}


