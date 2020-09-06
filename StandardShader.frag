#version 330 core

in vec2 f_uv;
in vec3 f_pos;
in vec3 f_normal;
in vec3 f_lightDirection;
in vec3 f_eyeDirection;

out vec3 color;

uniform sampler2D tex;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{

	vec3 matDiffuseColor = texture(tex, f_uv).rgb;
	vec3 matSpecularColor = vec3(0.3,0.3,0.3);
	vec3 matAmbientColor = vec3(0.1,0.1,0.1) * matDiffuseColor;

	vec3 n = normalize(f_normal);
	vec3 l = normalize(f_lightDirection);

	float dist = length( lightPos - f_pos );
	float diffuseCos = clamp(dot(n, l), 0, 1);
	float specularCos = clamp(dot(f_eyeDirection, reflect(-l, n)), 0, 1);

	color =
	matAmbientColor +
	(
		matDiffuseColor * diffuseCos 
		+ matSpecularColor * pow(specularCos, 5)
	)
	* lightColor / (dist * dist);
}