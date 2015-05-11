#version 420
out vec4 color;
in vec3 vsNormal;
in vec2 vsUV;
in vec3 lS;
in vec3 eyeDir;
layout (binding = 0) uniform sampler2D mainTexture;

void main()
{	
	
	vec3 fsNormal = normalize(vsNormal);
	vec3 reflection = reflect(-lS, fsNormal);
	float cosTheta = clamp(dot (fsNormal, lS), 0, 1);
	float cosAlpha = clamp( dot( eyeDir, reflection ), 0,1 );
	vec3 lC = vec3(0.6, 0.3, 0.7);
	color = cosTheta * texture(mainTexture, vsUV);
}