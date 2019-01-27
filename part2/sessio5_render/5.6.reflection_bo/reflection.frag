
#version 330 core
out vec4 fragColor;

uniform sampler2D colorMap;

uniform float SIZE;

const int W = 4; // filter size: 2W*2W

void main()
{

    //Obtenim les coordenades del fragment en el viewport respecte al tamany de la imatge
    //D'aquesta manera, al mapejar la imatge obtenida com a textura al pla donara la 
    //sensació de ser una reflexió
    vec2 st = (gl_FragCoord.xy - vec2(0.5)) / SIZE;
    
    //bk es una variable temporal per analitzar el color del fragment
    vec4 bk = texture(colorMap,st);

    //En cas que sigui de color blanc, pintem el color del pla
    if (bk.r == 1 && bk.g == 1 && bk.b == 1){
        fragColor = vec4(0.5,0.5,0.5,0);
    } else {
        //Else, pintem amb la imatge obtinguda
        fragColor = texture(colorMap,st);
    }   
}