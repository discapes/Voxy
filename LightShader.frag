#version 330 core

in vec2 f_uv;

out vec3 color;

uniform sampler2D tex;

void main()
{

	color = vec3(1,0.5,0);//texture(tex, f_uv).rgb;
}