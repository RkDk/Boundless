#version 410


in vec2 textureCoord;
smooth in vec4 textureColor;

uniform sampler2D texUnit;
uniform sampler2D texUnit2;
uniform sampler2D texUnit3;

out vec4 outputColor;

#define MAX_DIST .3

void main()
{

    vec4 shadow = texture( texUnit2, textureCoord );
    vec4 scene = texture( texUnit, textureCoord );
    vec4 light = texture( texUnit3, textureCoord ) * .4;
    vec4 scenelight = mix( scene, light, light.a );
    outputColor = scenelight * textureColor * shadow.r;

}

