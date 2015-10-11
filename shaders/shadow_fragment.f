#version 410


in vec2 textureCoord;
smooth in vec4 textureColor;

uniform sampler2D texUnit;
uniform sampler2D texUnit2;

out vec4 outputColor;

#define MAX_DIST 500


float PI = 3.14159;

float atan2(in float y, in float x)
{
    
    if( x == 0.0 ) 
        return sign(y)*PI/2.0;
        
    bool s = (abs(x) > abs(y));
    return mix(PI/2.0 - atan(x,y), atan(y,x), s);
    
}


void main()
{

    float dist = distance( textureCoord, vec2( .5, .5 ) );
    float angleFromCenter = atan2( textureCoord.y - .5, textureCoord.x - .5 );
    float range = 2.0 * PI;
    
    if( angleFromCenter < 0.0 ) {
    
        angleFromCenter = PI - abs( angleFromCenter ) + PI;
    
    }
    
    float coordx = angleFromCenter / range;
    vec4 shadowColor = texture( texUnit2, vec2( coordx, 0 ) );
    
    float mul = 1.5;

    if( dist > .3 )
        mul = .4;

    
    if( dist > shadowColor.r ) {
        float oldmul = mul;
        mul = dist * 1.2;
        if( oldmul < mul )
            mul = oldmul;
    }

    outputColor = texture( texUnit, textureCoord ) * textureColor * mul;

}

