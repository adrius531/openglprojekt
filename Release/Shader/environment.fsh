#version 330
uniform mat4 uModelMatrix;

uniform samplerCube uTexCubeMap;
uniform vec4 uLightPos0;
uniform vec4 uLightAmb0;
uniform vec4 uLightDif0;
uniform vec4 uLightSpec0;

uniform vec4 uMatAmb0;
uniform vec4 uMatDif0;
uniform vec4 uMatSpec0;
uniform float uMatShine0;

uniform mat4 uViewMatrix;

uniform vec3 uEyePos;

in vec3 vNormal;
in vec4 objPos;
in vec2 vTexCoord;
in vec3 VPosition;

out vec4 oColor;
uniform sampler2D uNormalmap;
uniform sampler2D uTexture;
uniform samplerCube uTexCubeM;


void main(){

    float dist          = length(vec3(objPos - uViewMatrix * uModelMatrix * uLightPos0));
    float attenuation   = 1.0/(1.0+0.0000000001*dist+0.00000000000001*dist*dist);
    vec3 amb            = vec3(texture2D(uTexture, vTexCoord).rgb * vec3(uLightAmb0));
    vec3 fLightD        = vec3(normalize(uViewMatrix * uModelMatrix * uLightPos0 - objPos));
    vec3 fNormal        = 2.0 * texture2D(uNormalmap, vTexCoord).rgb - vec3(1.0, 1.0, 1.0);
    float intDif        = max(dot(fLightD, fNormal), 0.0);
    vec3 dif            = vec3(intDif * texture2D(uTexture, vTexCoord).rgb * vec3(uLightDif0));
    vec3 view           = normalize(vec3(objPos)-uEyePos);
    vec3 viewR          = normalize(reflect(-view, fNormal));
    vec3 fLightR        = normalize(reflect(fLightD, fNormal));
    vec3  env           = vec3(texture(uTexCubeM, viewR).rgb);
    float intSpec       = pow(max(dot(view, -fLightR), 0.0), uMatShine0);
    vec3 spec           = vec3(intSpec * uMatSpec0 * uLightSpec0);
    oColor = vec4(((amb + dif + spec + env) * attenuation), 1.0);
}
