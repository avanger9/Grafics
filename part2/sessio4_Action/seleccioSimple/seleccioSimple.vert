#version 330 core

in  vec3 vertex;

uniform float sx, sy, sz;
uniform float tx, ty, tz;

uniform mat4  mv, mp;

void main()
{
    // matrius definides per columnes
    mat4 escala = mat4(vec4(sx,  0,  0, 0),
                       vec4( 0, sy,  0, 0),
                       vec4( 0,  0, sz, 0),
                       vec4( 0,  0,  0, 1)
                       );

    mat4 transla = mat4(vec4( 1,  0,  0, 0),
                        vec4( 0,  1,  0, 0),
                        vec4( 0,  0,  1, 0),
                        vec4(tx, ty, tz, 1)
                        );

    gl_Position  = mp * mv * transla * escala * vec4(vertex, 1.0);
}

