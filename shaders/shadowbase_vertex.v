#version 410

layout( location = 0 ) in vec2 position;
layout( location = 1 ) in vec4 color;
layout( location = 2 ) in vec2 st;

out vec2 textureCoord;
smooth out vec4 textureColor;

uniform mat4 ProjView;
uniform mat4 ModelMat;
uniform mat4 ViewMat;

void main()
{
   textureColor = color;
   textureCoord = st;

   vec4 pos = vec4( position.x, position.y, 1, 1 );

   gl_Position = ProjView * ModelMat * ViewMat * pos;

}
