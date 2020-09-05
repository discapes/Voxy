#version 330 core

layout(location = 0) in vec2 pos_windowspace;
layout(location = 1) in vec2 uv;

out vec2 f_uv;

void main()
{
	// map [0..800][0..600] to [-1..1][-1..1]
	vec2 pos_screenspace = pos_windowspace - vec2(400,300);
	pos_screenspace /= vec2(400,300);
	gl_Position =  vec4(pos_screenspace,0,1);
	f_uv = uv;
}

