#version 460 core

varying highp vec2 uv;
varying highp mat3 tbnMatrix_viewSpace;
varying highp vec4 fragmentPosition_viewSpace;

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


  gl_FragColor.rgb = (diffuseColor.rgb) + (specularColor.rgb);
  gl_FragColor.a = diffuseColor.a;
}