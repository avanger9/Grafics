#version 330 core

uniform vec4 lightAmbient;   // similar a gl_LightSource[0].ambient
uniform vec4 lightDiffuse;   // similar a gl_LightSource[0].diffuse
uniform vec4 lightSpecular;  // similar a gl_LightSource[0].specular
uniform vec4 lightPosition;  // similar a gl_LightSource[0].position (sempre estarà en eye space)

uniform vec4 matAmbient;     // similar a gl_FrontMaterial.ambient
uniform vec4 matDiffuse;     // similar a gl_FrontMaterial.diffuse
uniform vec4 matSpecular;    // similar a gl_FrontMaterial.specular
uniform float matShininess; // similar a gl_FrontMaterial.shininess

in vec3 n;
in vec3 p;
out vec4 fragColor;

vec4 light(vec3 n, vec3 v, vec3 l) {
	n = normalize(n);
	vec3 r = normalize(2*dot(n,l)*n-l);
	float NdotL=max(0, dot(n, l));
	float RdotV=max(0, dot(r, v));
	float ldiff=NdotL;
	float lspec=0;
	if (NdotL>0) lspec=pow(RdotV, matShininess);
	return matAmbient*lightAmbient + matDiffuse*lightDiffuse*ldiff + matSpecular*lightSpecular*lspec;
}

void main()
{
	vec3 v = normalize(-p);
	vec3 l = normalize(lightPosition.xyz - p);
    fragColor = light(n,v,l);
}
