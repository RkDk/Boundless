#version 410


in vec2 textureCoord;
smooth in vec4 textureColor;

uniform sampler2D texUnit;
uniform sampler2D spriteTex;

out vec4 outputColor;

void main()
{

    outputColor = vec4( 0, 0, 0, 0 );

    //We only cast shadows on pixels that are fairly visible to the player and are near the bottom of the entity
    if( textureCoord.y > .85 ) {
        vec4 color = texture( spriteTex, textureCoord );
        if( color.a > .1 )
            outputColor = texture( texUnit, textureCoord ) * textureColor;
    } 
      
}

