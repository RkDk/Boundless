#version 410


in vec2 textureCoord;
smooth in vec4 textureColor;

uniform sampler2D texUnit;
uniform sampler2D texUnit2;
uniform vec2 lightPos;

out vec4 outputColor;

#define MAX_DIST .7

void main()
{

    float RAD2DEG = 57.2957;
    float PI = 3.14159;
    float DEG2RAD = .0174532;
    float rayAngle = textureCoord.x * ( 2.0 * PI );
    outputColor = vec4( 1, 1, 1, 1 );
    
    for( int j = 0; j < 256; j++ ) {
    
        float d = (  j / 256.0 ) * MAX_DIST;
    
        float x = lightPos.x + ( cos( rayAngle ) * d );
        float y = ( 1 - lightPos.y ) - ( sin( rayAngle ) * d );
        vec4 color = texture( texUnit2, vec2( x, y ) );
        outputColor = vec4( 1, 1, 1, 1 );
        
        if( color.r > .1 ) {
            
            float dist = distance( vec2( x, y ), vec2( lightPos.x, ( 1 - lightPos.y ) ) );
            float c = dist;
            outputColor = vec4( c, c, c, 1 );
            return;
        
        }
    
    }

}

