#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec3 vnormal;

void main()
{
	vnormal = normal;
    gl_Position = vec4(vertex, 1.0);
}
