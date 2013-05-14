#version 120

//Bonus
const float FresnelPower=10;
const float FresnelReflectance = 0.2;

// sabit degiskenler
uniform mat4 MVP,ModelView;
uniform float color;

// diziden alinacak degiskenler
attribute vec4 Position;
attribute vec3 Normal;

// fragment shader'a aktarilacak veriler
varying vec3 i,j;
varying float Oran;
varying float varyingColor;
//varying vec3 normal;

// vertex shader main metodu
void main()
{	
    vec3 vVertex = vec3(ModelView * Position);

    i = normalize(vec3(0,0,-1));
    j = normalize(mat3(ModelView) * Normal);

    vec3 pos = vVertex;
    vec3 no = (mat3(ModelView) * Normal);

    //BONUS
    Oran = FresnelReflectance + (1.0 - FresnelReflectance) * pow((1.0 - dot(-i,j)), FresnelPower);

    varyingColor = color;

    // gl_Position ekranda noktanin nerede olacagini belirtir.
    gl_Position = MVP * Position;
    //normal = mat3(MVP)*Normal;
}