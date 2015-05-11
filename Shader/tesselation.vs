// Basic vertex shader for parallax mapping
#version 420

// attributes
//layout(location = 0) in vec3 i_position; // xyz - position
//layout(location = 1) in vec3 i_normal; // xyz - normal
//layout(location = 2) in vec2 i_texcoord0; // xy - texture coords
//layout(location = 3) in vec4 i_tangent; // xyz - tangent, w - handedness

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 tangent;
layout (location = 3) in vec3 bitangent;
layout (location = 4) in vec2 uv;


// uniforms
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat4 MVP;
uniform mat4 MV;
uniform mat3 MV3;
//Vllt NormalMatrix außerhalb berechnen
//uniform mat3 u_normal_mat;
uniform vec3 light_position;
uniform vec3 camera_position;

// data for fragment shader
out vec3 pos_ws;
out vec3 o_toLightInTangentSpace;
out vec3 o_toCameraInTangentSpace;

out vec2 vsUV;

///////////////////////////////////////////////////////////////////

void main(void)
{
  // vec3 camera_position = vec3(0, 0, 5);
   // transform to world space
   pos_ws = (M * vec4(position, 1.0f)).xyz;
   //NormalMatrix outsourcen
   mat3 M3 = mat3(M); 
   mat3 normalMatrix = transpose(inverse(mat3(M)));
   vec3 worldNormal = normalize(normalMatrix * normal);
   vec3 worldTangent = normalize(normalMatrix * tangent);
   vec3 worldBitangent = normalize(normalMatrix * -bitangent);

   // calculate vectors to the camera and to the light
   vec3 worldDirectionToLight = normalize(light_position - pos_ws);
   vec3 worldDirectionToCamera = normalize(pos_ws - camera_position);

   // calculate bitangent from normal and tangent
   

   // transform direction to the light to tangent space
   o_toLightInTangentSpace = vec3(
         dot(worldDirectionToLight, worldTangent),
         dot(worldDirectionToLight, worldBitangent),
         dot(worldDirectionToLight, worldNormal)
      );

   // transform direction to the camera to tangent space
   o_toCameraInTangentSpace= vec3(
         dot(worldDirectionToCamera, worldTangent),
         dot(worldDirectionToCamera, worldBitangent),
         dot(worldDirectionToCamera, worldNormal)
      );

   // pass texture coordinates to fragment shader
   vsUV = uv;

   // calculate screen space position of the vertex
   gl_Position = MVP * vec4(position, 1.0);
} 