#pragma once
#include "Shaders.h"
#include "Light.h"
#include "StandardModel.h"
#include "Camera.h"

class LightShaders : public Shaders
{
	const Camera& camera;

	GLuint uniMVP{};
	GLuint uniTex{};

public:
	LightShaders(const char* vertexShaderName, const char* fragmentShaderName, const Camera& camera);

	void draw(const StandardModel& model, const mat4& modelMatrix);

	~LightShaders();
};
