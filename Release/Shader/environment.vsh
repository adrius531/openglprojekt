#version 330

uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;
uniform mat4 uModelMatrix;
in vec3 aNormal;
in vec3 aPosition;
in vec2 aTexCoord;

out vec3 vNormal;
out vec4 objPos;
out vec3 vPosition;
out vec2 vTexCoord;

void main()
{   gl_Position  = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(aPosition, 1.0);
    objPos       = uModelMatrix * vec4(aPosition, 1.0);
    //vNormal     = uNormalMatrix * aNormal;
    vTexCoord    = aTexCoord;
    vNormal      = inverse(transpose(mat3(uViewMatrix * uModelMatrix))) * aNormal;
    vPosition    = aPosition;
}
