#version 410


in vec2 textureCoord;
smooth in vec4 textureColor;

uniform sampler2D texUnit;
uniform sampler2D texUnit2;
uniform vec2 lightPos;

out vec4 outputColor;

#define MAX_DIST .3

void main()
{

    float dist = distance( vec2( lightPos.x, lightPos.y ), textureCoord );
    outputColor = ( textureColor *  ( ( 1 / ( dist * 6 ) ) ) ) * .9;

}

