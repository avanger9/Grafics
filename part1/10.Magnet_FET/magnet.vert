#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrixInverse;
uniform mat3 normalMatrix;

uniform vec4 lightPosition;

uniform float n = 4;

void main()
{
	vec3 f = (modelViewMatrixInverse*lightPosition).xyz;
    vec3 N = normalize(normalMatrix * normal);
    
    float d = distance(vertex,f);
    float w = clamp(1/pow(d,n), 0, 1);
    
    vec3 v = (1-w)*vertex+w*f;
    frontColor = vec4(N.z);
    
    gl_Position = modelViewProjectionMatrix * vec4(v, 1.0);
}
