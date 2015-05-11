#version 420
// basic fragment shader for Parallax Mapping

// data from vertex shader
in vec2 vsUV;
in vec3 o_toLightInTangentSpace;
in vec3 o_toCameraInTangentSpace;

// textures
layout(binding = 0) uniform sampler2D mainTexture;
layout(binding = 2) uniform sampler2D heightMap;
layout(binding = 1) uniform sampler2D normalMap;

// color output to the framebuffer
out vec4 resultingColor;

vec2 TraceRay(in float height, in vec2 coords, in vec3 dir, in float mipmap){

    vec2 NewCoords = coords;
    vec2 dUV = - dir.xy * height * 0.05;
    float SearchHeight = 1.0;
    float prev_hits = 0.0;
    float hit_h = 0.0;

    for(int i=0;i<10;i++){
        SearchHeight -= 0.1;
        NewCoords += dUV;
        float CurrentHeight = textureLod(normalMap,NewCoords.xy, mipmap).a;
        float first_hit = clamp((CurrentHeight - SearchHeight - prev_hits) * 499999.0,0.0,1.0);
        hit_h += first_hit * SearchHeight;
        prev_hits += first_hit;
    }
    NewCoords = coords + dUV * (1.0-hit_h) * 10.0f - dUV;

    vec2 Temp = NewCoords;
    SearchHeight = hit_h+0.1;
    float Start = SearchHeight;
    dUV *= 0.2;
    prev_hits = 0.0;
    hit_h = 0.0;
    for(int i=0;i<5;i++){
        SearchHeight -= 0.02;
        NewCoords += dUV;
        float CurrentHeight = textureLod(normalMap,NewCoords.xy, mipmap).a;
        float first_hit = clamp((CurrentHeight - SearchHeight - prev_hits) * 499999.0,0.0,1.0);
        hit_h += first_hit * SearchHeight;
        prev_hits += first_hit;    
    }
    NewCoords = Temp + dUV * (Start - hit_h) * 50.0f;

    return NewCoords;
}

void main( void )
{
   vec3  fvLightDirection = normalize( o_toLightInTangentSpace );
   vec3  fvViewDirection  = normalize( o_toCameraInTangentSpace );

   float mipmap = 0;

   vec2 NewCoord = TraceRay(0.1,vsUV,fvViewDirection,mipmap);

   //vec2 ddx = dFdx(NewCoord);
   //vec2 ddy = dFdy(NewCoord);

   vec3 BumpMapNormal = textureLod(normalMap, NewCoord.xy, mipmap).xyz;
   BumpMapNormal = normalize(2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0));

   vec3  fvNormal         = BumpMapNormal;
   float fNDotL           = dot( fvNormal, fvLightDirection ); 

   vec3  fvReflection     = normalize( ( ( 2.0 * fvNormal ) * fNDotL ) - fvLightDirection ); 
   float fRDotV           = max( 0.0, dot( fvReflection, fvViewDirection ) );

   vec4  fvBaseColor      = textureLod( mainTexture, NewCoord.xy, mipmap);

   vec4 fvDiffuse = vec4(1.0, 1.0, 1.0, 1.0);
   vec4 fvAmbient = vec4(0.1, 0.1, 0.1, 1.0);
   vec4 fvSpecular = vec4(0.8, 1.0, 1.0, 1.0);
   float fSpecularPower = 2.0;
   
   vec4  fvTotalAmbient   = fvAmbient * fvBaseColor; 
   vec4  fvTotalDiffuse   = fvDiffuse * fNDotL * fvBaseColor; 
   vec4  fvTotalSpecular  = fvSpecular * ( pow( fRDotV, fSpecularPower ) );

   resultingColor = ( fvTotalAmbient + (fvTotalDiffuse + fvTotalSpecular) );

}