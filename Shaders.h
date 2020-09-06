#pragma once
#include "includes.h"
#include "Model.h"

class Shaders
{
public:
	GLuint program{};
	virtual void draw(Model& model, mat4 modelMatrix) = 0;
	virtual void draw(Model& model, vec3 location) = 0;
	virtual void build() = 0;
	virtual ~Shaders() {};
};