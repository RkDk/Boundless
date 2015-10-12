#version 410


in vec2 textureCoord;
smooth in vec4 textureColor;

uniform sampler2D texUnit;
uniform sampler2D texUnit2;

out vec4 outputColor;

void main()
{

    outputColor = vec4( 0, 0, 0, 0 );

    if( textureCoord.y > .85 ) {
        vec4 color = texture( texUnit2, textureCoord );
        if( color.a > .1 )
            outputColor = texture( texUnit, textureCoord ) * textureColor;
    } 
      
}

