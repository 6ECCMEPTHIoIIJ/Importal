#version 460 core

in highp vec2 uv;
in highp mat3 tbnMatrix_viewSpace;
in highp vec4 fragmentPosition_viewSpace;

out vec4 color;

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

  color.rgb = (diffuseColor.rgb) ;
  color.a = diffuseColor.a;
}