#version 420
out vec3 color;

in vec3 vsNormal;
in vec2 vsUV;
in vec3 lightDir1_ts;
in vec3 eyeDir_ts;
in vec3 lightDir1_cs;
in vec3 eyeDir_cs;
in vec3 pos_ws;

layout(binding = 0) uniform sampler2D mainTexture;
layout(binding = 2) uniform sampler2D heightMap;
layout(binding = 1) uniform sampler2D normalMap;

void main()
{
	//ALS UNIFORM OUTSOURCEN
	vec3 light1_ws = vec3(-1.0f, -1.0f, 1.0f);
	
	//LIGHTS
	vec3 light1Color = vec3 (1.0, 1.0, 1.0);
	float light1Power = 20.0;
	vec3 diffuseColor = texture2D(mainTexture, vsUV).rgb;
	vec3 ambientColor = vec3(0.1, 0.1, 0.1) * diffuseColor;
	vec3 specularColor = vec3(0.2, 0.2, 0.1);
	//vec3 specularColor = texture2D( SpecularTextureSampler, UV ).rgb * 0.3;
	
	vec3 normal_ts = texture2D(normalMap, vsUV).rgb * 2.0f - 1.0f;
	float dist = length(light1_ws - pos_ws);
	vec3 l = normalize(lightDir1_ts);
	// Cosine of the angle between the normal and the light direction, 
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp(dot (normal_ts, l), 0, 1);
	
	vec3 eye = normalize(eyeDir_ts);
	vec3 reflection = reflect(-l, normal_ts);
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp( dot( eye, reflection ), 0,1 );
	
	color = ambientColor + (diffuseColor * light1Color) * light1Power * (cosTheta / (dist * dist))
	  + specularColor * light1Color * light1Power * (pow(cosAlpha, 5) / (dist * dist));
		// Ambient : simulates indirect lighting
		
		// Diffuse : "color" of the object
		
		// Specular : reflective highlight, like a mirror
		
}