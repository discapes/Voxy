#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;

out vec2 f_uv;

uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(pos, 1);
	f_uv = uv;
}