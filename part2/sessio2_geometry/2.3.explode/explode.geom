#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

uniform mat4 modelViewProjectionMatrix;

in vec4 vfrontColor[];
in vec3 vnormal[];
out vec4 gfrontColor;

const float speed = 0.5;
uniform float time;

void main( void )
{
	vec3 n = speed*time*(vnormal[0]+vnormal[1]+vnormal[2])/3;
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		vec3 v = gl_in[i].gl_Position.xyz+n;
		gl_Position = modelViewProjectionMatrix*vec4(v,1);
		EmitVertex();
	}
    EndPrimitive();
}
