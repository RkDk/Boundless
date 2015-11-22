#version 410


in vec2 textureCoord;
smooth in vec4 textureColor;

uniform sampler2D texUnit;
uniform sampler2D shadowObjTex;
uniform vec2 lightPos;

out vec4 outputColor;

#define MAX_DIST 1.5

void main()
{

    const float RAD2DEG = 57.2957;
    const double PI = 3.14159265359;
    const float DEG2RAD = .0174532;
    const int numLoops = 256;
    const float loopMul = 1.0 / float( numLoops );
    
    //Determine ray angle as a radian in range [0:2pi]
    float rayAngle = float( double( textureCoord.x ) * ( 2.0 * PI ) );
    outputColor = vec4( 1, 1, 1, 1 );
    
    for( int j = 0; j < numLoops; j++ ) {
    
        //Calculate a distance from the light origin to test at.
        float d = (  j * loopMul ) * MAX_DIST;
    
        //Calculate texture position at certain distance from the origin at a certain angle
        float x = lightPos.x + ( cos( rayAngle ) * d );
        float y = ( 1 - lightPos.y ) - ( sin( rayAngle ) * d );
    
        //Get color at this position in our shadow objects texture
        vec4 color = texture( shadowObjTex, vec2( x, y ) );
        
        outputColor = vec4( 1, 1, 1, 1 );
        
        //Something is there in the texture, so we should begin casting a shadow here
        if( color.r > .1 ) {
            
            //The resulting color is based off of the distance from the origin
            float dist = distance( vec2( x, y ), vec2( lightPos.x, ( 1 - lightPos.y ) ) );
            float c = dist;
            outputColor = vec4( c, c, c, 1 );
            return;
        
        }
    
    }

}

