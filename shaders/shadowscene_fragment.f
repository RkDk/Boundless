#version 410


in vec2 textureCoord;
smooth in vec4 textureColor;

uniform sampler2D texUnit;
uniform sampler2D entityTex;
uniform sampler2D shadowTex;

out vec4 outputColor;

void main()
{

    vec4 entityColor = texture( entityTex, textureCoord );
    vec4 sceneColor = texture( texUnit, textureCoord );
    vec4 shadowColor = texture( shadowTex, vec2( textureCoord.x, 1.0 - textureCoord.y ) );
    
    outputColor = mix( sceneColor, entityColor, entityColor.a );
    
    if( entityColor.a < .001 ) {
    
        float shadowMul = shadowColor.r;
        
        if( shadowColor.r > .99 )
            shadowMul = 1;
        
        outputColor = sceneColor * shadowMul;
    
    }
    
    //outputColor = shadowColor;
    
    //vec4 shadow = texture( entityTex, textureCoord );
    //vec4 scene = texture( texUnit, textureCoord );
    //vec4 light = texture( shadowTex, textureCoord ) * .4;
    //vec4 scenelight = mix( scene, light, light.a );
    //outputColor = scenelight * textureColor * shadow.r;

}

