#version 120

varying vec3 i,j;
varying float Oran;

varying float varyingColor;

// vertex shaderindan gelen veriler
//varying vec3 normal;

// fragment shader main metodu
void main(void)
{	
    float cos = dot(i, normalize(j));
    vec3 color = mix(vec3(0,0,0),vec3(1,1,0), cos + 1);


gl_FragColor = vec4(color, 1.0);

    // gl_FragColor ekrana basilacak rengi secer

}
