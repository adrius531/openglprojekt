#version 420
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat4 MVP;
uniform mat3 MV3;
uniform vec3 light_position;
uniform vec3 camera_position;

out vec3 vsNormal;
out vec2 vsUV;
out vec3 lS;
out vec3 eyeDir;
void main()
{
	vec3 pos_ws = (M * vec4(position, 1.0f)).xyz;
	mat3 normalMatrix = transpose(inverse(mat3(M)));
	vsUV = uv;
	lS = light_position - pos_ws;
	eyeDir = pos_ws - camera_position;
	vsNormal = normalize(normalMatrix * normal);
	//testColor = M*vec4(1.0f, 1.0f, 1.0f, 1.0);
	
	gl_Position = MVP*vec4(position, 1.0);
}