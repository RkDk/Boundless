#version 410


in vec2 textureCoord;
smooth in vec4 textureColor;

uniform sampler2D texUnit;
uniform sampler2D texUnit2;

out vec4 outputColor;

#define MAX_DIST .3

void main()
{

    vec4 color = texture( texUnit2, textureCoord );
    outputColor = texture( texUnit, textureCoord ) * textureColor * color.r;

}

