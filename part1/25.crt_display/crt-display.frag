#version 330 core

in vec4 frontColor;
out vec4 fragColor;
uniform int n;

void main()
{
    fragColor = frontColor;
    if (int(gl_FragCoord.y-	0.5)%n != 0) discard;
    
}
