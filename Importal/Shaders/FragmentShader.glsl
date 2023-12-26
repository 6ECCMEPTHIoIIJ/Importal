#version 460 core
//
//in vec2 uv;
//in mat3 tbnMatrix_viewSpace;
//in vec4 fragmentPosition_viewSpace;
//in vec4 fragmentPosition_worldSpace;
//in vec3 fragmentNormal;
//
//out vec4 color;
//
//layout (location = 4) uniform vec3 lightPos;
//
//uniform sampler2D texture_diffuse1;
////uniform sampler2D texture_diffuse2;
////uniform sampler2D texture_diffuse3;
//uniform sampler2D texture_specular1;
////uniform sampler2D texture_specular2;
//uniform sampler2D texture_normal1;
////uniform sampler2D texture_normal2;
//
//void main() {
//  highp vec4 normalColor = texture2D(texture_normal1, uv);
//  highp vec4 diffuseColor = texture2D(texture_diffuse1, uv);
//  highp vec3 specularColor = vec3(diffuseColor.rgb);
//  
//  
//  vec3 norm = normalize(fragmentNormal);
//  vec3 lightDir = normalize(lightPos - vec3(fragmentPosition_worldSpace)); 
//  float diff = max(dot(norm, lightDir), 0.0);
//
//  vec3 someColor = vec3(1.0f, 1.0f, 1.0f);
//  vec3 ambient = someColor * .0f;
//
//  color.rgb = diff * (diffuseColor.rgb);
//  color.a = diffuseColor.a;
//}

struct LightProperty{
    vec3 ambienceColor;
    vec3 diffuseColor;
    vec3 specularColor;

    vec4 position;
    vec4 direction;
    float cutoff;
    float power;
    int type;
};

layout (location = 7) uniform sampler2D texture_diffuse1;
layout (location = 9) uniform sampler2D shadowMap;
layout (location = 11) uniform int countLights;
layout (location = 13) uniform int indexLightForShadow;
layout (location = 15) uniform float lightPower;
layout (location = 20) uniform LightProperty light[100];

in vec4 v_position;
in vec2 v_textCoord;
in vec3 v_normal;
in highp vec4 v_positionLightMatrix;
in highp mat4 v_viewMatrix;

out vec4 color;

LightProperty v_lightProperty[100];

float SampleShadowMap(sampler2D map, vec2 coords, float compare){
    vec4 v = texture2D(map, coords);
    float value = v.x * 255.0 + (v.y * 255.0 + (v.z * 255.0 + v.w) / 255.0) / 255.0;
    return step(compare, value); //return value > compare
}

float SampleShadowMapLinear(sampler2D map, vec2 coords, float compare, vec2 texelSize){
    vec2 pixelPos = coords / texelSize + 0.5;
    vec2 fractPart = fract(pixelPos);
    vec2 startTexel = (pixelPos - fractPart) * texelSize;

    float blTexel = SampleShadowMap(map, startTexel, compare);
    float brTexel = SampleShadowMap(map, startTexel + vec2(texelSize.x, 0), compare);
    float tlTexel = SampleShadowMap(map, startTexel + vec2(0, texelSize.y), compare);
    float trTexel = SampleShadowMap(map, startTexel + texelSize, compare);

    float mixA = mix(blTexel, tlTexel, fractPart.y);
    float mixB = mix(brTexel, trTexel, fractPart.y);

    return mix(mixA, mixB, fractPart.x);
}

float SampleShadowMapPCF(sampler2D map, vec2 coords, float compare, vec2 texelSize){
    float result = 0.f;
    for(float y = -2.0; y < 2.0; y+= 1.0)
        for(float x = -2.0; x < 2.0; x+= 1.0){
            vec2 offset = vec2 (x, y) * texelSize;
            result += SampleShadowMapLinear(map, coords + offset, compare, texelSize);
        }

    return result / 25.0;
}

float CalcShadowAmount(sampler2D map, vec4 initialShadowCoords){
    vec3 tmp = v_positionLightMatrix.xyz / v_positionLightMatrix.w;
    tmp = tmp * vec3(0.5) + vec3(0.5);
    float offset =2.0;
    offset *= dot(v_normal, v_lightProperty[indexLightForShadow].direction.xyz);
    return SampleShadowMapPCF(shadowMap, tmp.xy, tmp.z * 255.0 - 2.f, vec2(1.0/1024.0));
}

void main(void)
{
    for (int i = 0; i < countLights ; i++){
        v_lightProperty[i].ambienceColor = light[i].ambienceColor;
        v_lightProperty[i].diffuseColor = light[i].diffuseColor;
        v_lightProperty[i].specularColor = light[i].specularColor;
        v_lightProperty[i].cutoff = light[i].cutoff;
        v_lightProperty[i].type = light[i].type;
        v_lightProperty[i].direction = v_viewMatrix * light[i].direction;
        v_lightProperty[i].position = v_viewMatrix * light[i].position;
        v_lightProperty[i].power = light[i].power;
    }

    float shadowCoef = 1.0;

//    if(v_lightProperty[u_indexLightForShadow].type == 0)
//        shadowCoef = CalcShadowAmount(u_shadowMap, v_positionLightMatrix);
//    else
//        shadowCoef = 0.9f;

    vec4 resultColor = vec4(0.f, 0.f, 0.f, 0.f);
    vec4 eyePosition = vec4(0.f, 0.f, 0.f, 1.f);

    vec4 diffMatColor = /*vec4(1.f, 1.f, 1.f, 1.f);*/ texture2D(texture_diffuse1, v_textCoord);
    vec3 eyeVect = normalize(v_position.xyz - eyePosition.xyz);

    for (int i = 0; i < countLights ; i++){
        vec4 resultLightColor = vec4(0.f, 0.f, 0.f, 1.f);
        vec3 lightVect;
        if(v_lightProperty[i].type == 0){
            lightVect = normalize(v_lightProperty[i].direction.xyz);
        }else{

            lightVect = normalize(v_position - v_lightProperty[i].position).xyz;
            if(v_lightProperty[i].type == 2){
            
                float angle = acos(dot(normalize(v_lightProperty[i].direction.xyz), lightVect.xyz));
                if(angle > v_lightProperty[i].cutoff)
                    lightVect = vec3(0.f, 0.f, 0.f);
            }
        }

        vec3 reflectLight = normalize(reflect(lightVect, v_normal));

        float len = length(v_position.xyz - v_lightProperty[i].position.xyz);
        float specularFactor = 1000.f;
        float ambientFactor = 0.05f;

        vec4 diffColor, ambientColor, specularColor;
        if (v_lightProperty[i].type != 0) {
            diffColor = diffMatColor * light[i].power * max(0.f, dot(v_normal, - lightVect)) / (1.0f + 0.25f * pow(len, 2.f));
            specularColor = vec4(v_lightProperty[i].specularColor, 1.f) * light[i].power * pow(max(0.f, dot(reflectLight, -eyeVect)), specularFactor) / (1.0f + 0.25f * pow(len, 2.f));
        } else {
            diffColor = diffMatColor * light[i].power * max(0.f, dot(v_normal, - lightVect));
            specularColor = vec4(v_lightProperty[i].specularColor, 1.f) * light[i].power * pow(max(0.f, dot(reflectLight, -eyeVect)), specularFactor);
        }


        ambientColor = ambientFactor * vec4(v_lightProperty[i].ambienceColor, 1.f);
        resultLightColor += diffColor * vec4(v_lightProperty[i].diffuseColor, 1.f);
        resultLightColor += ambientColor;
        resultLightColor += specularColor;

        resultColor += resultLightColor;
    }
    shadowCoef += 0.2;
    if(shadowCoef > 1.0)
        shadowCoef = 1.0;

        if(shadowCoef > 0.2){

        }


    color = resultColor + diffMatColor * (1.f - shadowCoef) ;
}
