#version 410


in vec2 textureCoord;
smooth in vec4 textureColor;

uniform sampler2D texUnit;
uniform vec2 lightPos;

out vec4 outputColor;

#define MAX_DIST .3

void main()
{

    float dist = distance( vec2( lightPos.x, lightPos.y ), textureCoord );
    vec4 oldColor = texture( texUnit, textureCoord );
    vec4 newColor = max( 1 - dist * 2, 0 ) * textureColor;
   
    newColor = newColor + oldColor;
    outputColor = newColor;
    outputColor.a = 1;
    

}

