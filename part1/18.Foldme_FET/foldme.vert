#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;

uniform float time;

void main()
{
	float a = -time*texCoord.s;
	mat3 r = mat3(vec3(cos(a), 0, sin(a)),
				  vec3(0,      1,      0),
				  vec3(-sin(a),0, cos(a)));
	
    vec3 vert = vertex*r;
    frontColor = vec4(0,0,1,1);
    gl_Position = modelViewProjectionMatrix * vec4(vert, 1.0);
}
