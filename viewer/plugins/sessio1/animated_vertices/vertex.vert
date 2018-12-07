#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float time;
uniform float amplitude = 0.1;
uniform float freq = 1;
float PI = acos(-1.0);

void main()
{
    vec3 n = normalize(normalMatrix * normal);
    vec3 v = vertex + normal*abs(amplitude*sin(2*PI*freq*time));
    frontColor = vec4(vec3(n.z),1);
    gl_Position = modelViewProjectionMatrix * vec4(v, 1.0);
}
