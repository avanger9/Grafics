#version 330 core

in vec3 gnormal;
in vec3 gpos;
out vec4 fragColor;

uniform sampler2D grass_top0;
uniform sampler2D grass_side1;

uniform float d=0.1;

void main() {
	// grass side
	vec2 grassSideST = vec2(4*(gpos.x-gpos.y), 1.0-gpos.z/d);
	vec4 tgs = texture2D(grass_side1, grassSideST);
	// grass top
	vec2 grassTopST = 4*gpos.xy;
	vec4 tgt = texture2D(grass_top0, grassTopST);
	if (gnormal.z==0) {
		// vertical
		if (tgs.a < 0.1) discard;
		else fragColor = tgs;
	}
	else {
		// horitzontal
		fragColor = tgt;
	}
}