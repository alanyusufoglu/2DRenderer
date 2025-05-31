
#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;


out vec2 v_texCoord;

uniform mat4 u_Transform;


void main()
{
    gl_Position =u_Transform* position;
   
    v_texCoord = texCoord;
}

#shader fragment
#version 330 core

in vec2 v_texCoord;
out vec4 color;

uniform sampler2D u_texture;
uniform vec4 uColor;

void main()
{
    vec4 texColor = texture(u_texture, v_texCoord);
     color =  uColor;
; // Örnek: rengi doku ile çarpabilirsiniz
}
