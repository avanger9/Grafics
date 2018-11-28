#version 330 core

in vec4 frontColor;
out vec4 fragColor;
out vec3 N;

void main()
{
	vec3 normal=normalize(cross(dFdx(N), dFdy(N)));
    fragColor = frontColor*normal.z;
}
