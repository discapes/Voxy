#pragma once
#include "includes.h"
#include "Model.h"

class Shaders
{
public:
	virtual void draw(Model& model, Camera* camera, mat4 modelMatrix) = 0;
	virtual void draw(Model& model, Camera* camera, vec3 location) = 0;
	virtual void build() = 0;
	virtual ~Shaders() {};
};