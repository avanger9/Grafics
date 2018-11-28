#version 330 core

in vec3 p;
in vec3 n;

uniform mat4 modelViewMatrixInverse;

uniform float time;
uniform bool rotate = true;

// V, N, P, lightPos han d'estar al mateix espai de coordenades
// V és el vector unitari cap a l'observador
// N és la normal
// P és la posició 
// lightPos és la posició de la llum
// lightColor és el color de la llum
vec4 light(vec3 V, vec3 N, vec3 P, vec3 lightPos, vec3 lightColor) {
	const float shininess=100.0;
	const float Kd=0.5;
	N=normalize(N);
	vec3 L=normalize(lightPos-P);
	vec3 R=reflect(-L, N);
	float NdotL=max(0.0, dot(N, L));
	float RdotV=max(0.0, dot(R, V));
	float spec=pow(RdotV, shininess);
	return vec4(Kd*lightColor*NdotL+vec3(spec), 0);
}

void main()
{
	vec3 v = normalize(modelViewMatrixInverse[3].xyz-p);
	vec3 p1 = vec3(0,10,0);   vec3 c1 = vec3(0,1,0);
	vec3 p2 = vec3(0,-10,0);  vec3 c2 = vec3(1,1,0);
	vec3 p3 = vec3(10,0,0);   vec3 c3 = vec3(0,0,1);
	vec3 p4 = vec3(-10,0,0);  vec3 c4 = vec3(1,0,0);
	
	if (rotate) {
		mat3 r = mat3(vec3(cos(time), -sin(time), 0),
					  vec3(sin(time), cos(time),  0),
					  vec3(0,         0,          1));
		p1 *= r;
		p2 *= r;
		p3 *= r;
		p4 *= r;			
	}
	p1 = (modelViewMatrixInverse*vec4(p1, 1)).xyz;
	p2 = (modelViewMatrixInverse*vec4(p2, 1)).xyz;
	p3 = (modelViewMatrixInverse*vec4(p3, 1)).xyz;
	p4 = (modelViewMatrixInverse*vec4(p4, 1)).xyz;
	
	gl_FragColor = light(v,n,p,p1,c1) + light(v,n,p,p2,c2) + 
				   light(v,n,p,p3,c3) + light(v,n,p,p4,c4);
}
