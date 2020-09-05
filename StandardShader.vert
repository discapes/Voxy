#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;

out vec2 f_uv;
out vec3 f_pos;
out vec3 f_normal;
out vec3 f_lightDirection;
out vec3 f_eyeDirection;

uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform vec3 lightPos;

void main()
{
	gl_Position = MVP * vec4(pos, 1);
	f_uv = uv;
    vec4 pos_w = M * vec4(pos, 1);
	f_pos = pos_w.xyz;
	f_normal = (M * vec4(normal, 0)).xyz;;
	f_lightDirection = lightPos - f_pos;
	f_eyeDirection = normalize(vec3(0,0,0) - (V * pos_w).xyz);
}