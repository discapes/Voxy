#pragma once
#include "includes.h"
#include "StandardModel.h"

class Shaders
{
public:
	GLuint program{};
	virtual void draw(const StandardModel& model, const mat4& modelMatrix) = 0;
	void draw(const StandardModel& model, vec3 location)
	{
		return draw(model, glm::translate(mat4(1), location));
	}
	virtual ~Shaders() {};
};