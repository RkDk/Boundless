#version 410


in vec2 textureCoord;
smooth in vec4 textureColor;

uniform sampler2D texUnit;
uniform sampler2D shadowOccTex;
uniform vec2 lightPos;

out vec4 outputColor;

const float PI = 3.14159;

float atan2(in float y, in float x) {
    if( x == 0.0 ) 
        return sign(y)*PI/2.0;    
    bool s = (abs(x) > abs(y));
    return mix(PI/2.0 - atan(x,y), atan(y,x), s);
}


void main()
{

    //The maximum distance to consider drawing a shadow for an occluded pixel
    const float MAX_DIST = 1200.0;
    const float range = 2.0 * PI;
    
    //Get current pixel's color
    vec4 color = texture( texUnit, textureCoord );
    
    //Distance of current pixel from light origin
    float dist = distance( textureCoord, vec2( lightPos.x, lightPos.y ) );
    
    //Texture of shadow pixel from light origin
    float angleFromCenter = atan2( textureCoord.y - lightPos.y, textureCoord.x - lightPos.x );
    
    //Convert negative radians to positive equivalent
    if( angleFromCenter < 0.0 ) {
        angleFromCenter = PI - abs( angleFromCenter ) + PI;
    }
    
    //Get the x texture coordinate based off of angle from light origin
    float coordx = angleFromCenter / range;
    
    //Get occlusion texture color, will indicate if there is something here that can cast a shadow
    vec4 shadowColor = texture( shadowOccTex, vec2( coordx, 0 ) );
    
    //DEFUNCT
    //float mul = 1 - dist * 1;
    //if( dist < .1 )
    //    mul = mul + ( .1 - dist ) * 10;
    
    float mul = 1;

    //Shadow's red color is distance where the shadow starts; check to see if current pixel is in shadow
    if( dist > shadowColor.r ) {
        
        //float oldmul = mul;
        //mul = dist * 1.2;
        //if( oldmul < mul )
            //mul = oldmul;
    
        //Check to see if we're casting a shadow over an already lit pixel
        if( color.r > 0 ) {
        
            outputColor = vec4( .65, .65, .65, 1 );
        
        } else
            outputColor = vec4( 0, 0, 0, 1 );
       
        
    } else {
    
        //Otherwise, we're in a lit pixel.  Check to see if this lit pixel casts over a different light's shadow
        if( color.r < 1 && color.a > 0 ) {
        
            outputColor = vec4( .65, .65, .65, 1 );
        
        } else {
        
            if( color.a < .001 )
                outputColor = vec4( 1, 1, 1, 1 );
            else
                outputColor = color;
    
        }
        
    
    
    }

    //outputColor = color * textureColor * ( mul * 2 );

}

