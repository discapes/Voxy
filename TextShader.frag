#version 330 core

in vec2 f_uv;

out vec4 color;

uniform sampler2D fontAtlas;

void main()
{
	color = texture(fontAtlas, f_uv);
}