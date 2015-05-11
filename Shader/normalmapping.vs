#version 420
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 tangent;
layout (location = 3) in vec3 bitangent;
layout (location = 4) in vec2 uv;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat4 MVP;
uniform mat4 MV;
uniform mat3 MV3;
uniform vec3 light_position;
uniform vec3 camera_position;

out	vec3 eyeDir_ts;
out vec3 eyeDir_cs;
out vec3 vsNormal;
out vec3 pos_ws;
out vec2 vsUV;
out vec3 lightDir1_ts;
out vec3 lightDir1_cs;

void main()
{       
	//Als UNIFORM LIGHT outsourcen
	vec4 light1_ws = vec4(light_position, 1.0f);
	vec4 camera_ws = vec4(camera_position, 1.0f);
	mat3 normalMatrix = transpose(inverse(MV3));
	vsUV = uv;
	//vsNormal = normalize(vec3(normalMatrix * vec4(normal, 0.0f)));
	pos_ws = (M * vec4(position, 1.0f)).xyz;
	vec3 pos_cs = (V * vec4(pos_ws, 1.0f)).xyz;
	
	vec3 camera_cs = (V * camera_ws).xyz;
	eyeDir_cs = camera_cs - pos_cs;
	//BESSER 3x3 MATRIX ALS UNIFORM
	vec3 tangent_cs = normalize(normalMatrix * tangent);
	vec3 bitangent_cs = normalize(normalMatrix * bitangent);
	vec3 normal_cs = normalize(normalMatrix * normal);
	
	vec3 light1_cs = (V * light1_ws).xyz;
	lightDir1_cs = light1_cs - pos_cs;
	
	mat3 TBN = transpose(mat3(
        tangent_cs,
        bitangent_cs,
        normal_cs
    ));
        
	lightDir1_ts = TBN * lightDir1_cs;
	eyeDir_ts = TBN * eyeDir_cs;
	
	gl_Position = MVP*vec4(position, 1.0);
}