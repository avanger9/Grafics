#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

vec4 yellow = vec4(1,1,0,1);
vec4 red = vec4(1,0,0,1);

float a=1.0/9;

bool isYellow(float f) {
  return (f>=0 && f<a)
    || (f>=2*a && f<3*a) 
    || (f>=4*a && f<5*a)
    || (f>=6*a && f<7*a)
    || (f>=8*a && f<9*a); 
}

void main()
{
    float f = fract(vtexCoord.s);
    if (isYellow(f)) fragColor = yellow;
    else fragColor = red;
}
