#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMax;
uniform vec3 boundingBoxMin;

in vec4 vfrontColor[];
out vec4 gfrontColor;

vec4 black = vec4(0,0,0,0);
const vec4 cyan = vec4(0, 1, 1, 1);

void floorVertex(bool x, bool z, vec3 RC, float R) {
	gfrontColor = cyan;
	
	if (x) RC.x += R;
	else RC.x -= R;

	if (z) RC.z += R;
	else RC.z -= R;
	
	gl_Position = modelViewProjectionMatrix * vec4(RC, 1);
	EmitVertex();
}

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
    
    for (int i=0; i<3; ++i) {
    	gfrontColor = black;
    	vec4 v = gl_in[i].gl_Position;
    	v.y = boundingBoxMin.y;
    	gl_Position = modelViewProjectionMatrix*v;
    	EmitVertex();
    }
    EndPrimitive();
	
	if (gl_PrimitiveIDIn == 0) { 
		float r = length(boundingBoxMax-boundingBoxMin)/2;
		vec3 rc = (boundingBoxMax+boundingBoxMin)/2;
		rc.y = boundingBoxMin.y-0.01;
		floorVertex(false, false, rc, r);
		floorVertex(true, false, rc, r);
		floorVertex(false, true, rc, r);
		floorVertex(true, true, rc, r);
		EndPrimitive();
	}
}

