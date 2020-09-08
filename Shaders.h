#pragma once
#include "includes.h"
#include "Model.h"

class Shaders
{
public:
	GLuint program{};
	virtual void draw(const Model& model, const mat4& modelMatrix) = 0;
	virtual void draw(const Model& model, vec3 location) = 0;
	virtual void drawCube(const mat4& modelMatrix) = 0;
	virtual ~Shaders() {};
};