#version 330 core

in vec4 frontColor;
in vec3 n;
out vec4 fragColor;

void main()
{
    fragColor = frontColor*n.z;
}
