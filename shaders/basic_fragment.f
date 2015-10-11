#version 410


in vec2 textureCoord;
smooth in vec4 textureColor;

uniform sampler2D texUnit;

out vec4 outputColor;


void main()
{

   outputColor = texture( texUnit, textureCoord ) * textureColor;
   
}

