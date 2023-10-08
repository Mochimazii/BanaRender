#version 330
layout(location = 0) in vec4 a_position;
layout(location = 1) in vec2 a_normal;
layout(location = 2) in vec2 a_texCoord0;

out vec2 v_texCoord0;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * a_position;
    v_texCoord0 = a_texCoord0;
}