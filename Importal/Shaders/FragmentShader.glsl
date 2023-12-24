#version 460 core

in vec2 uv;
in mat3 tbnMatrix_viewSpace;
in vec4 fragmentPosition_viewSpace;
in vec4 fragmentPosition_worldSpace;
in vec3 fragmentNormal;

out vec4 color;

layout (location = 4) uniform vec3 lightPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_normal1;
uniform sampler2D texture_normal2;

void main() {
  highp vec4 normalColor = texture2D(texture_normal1, uv);
  highp vec4 diffuseColor = texture2D(texture_diffuse1, uv);
  highp vec3 specularColor = vec3(diffuseColor.rgb);
  
  
  vec3 norm = normalize(fragmentNormal);
  vec3 lightDir = normalize(lightPos - vec3(fragmentPosition_worldSpace)); 
  float diff = max(dot(norm, lightDir), 0.0);

  vec3 someColor = vec3(1.0f, 1.0f, 1.0f);
  vec3 ambient = someColor * .0f;

  color.rgb = diff * (diffuseColor.rgb);
  color.a = diffuseColor.a;
}