#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

out vec4 frontColor;
out vec2 vtexCoord;

out vec3 n;
out vec3 p;

uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main()
{
    n = normalize(normalMatrix * normal);
    p = (modelViewMatrix*vec4(vertex.xyz, 1)).xyz;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
