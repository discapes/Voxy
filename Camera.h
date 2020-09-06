#pragma once
#include "includes.h"
#include "Macros.h"

class Camera
{
public:
	ViewOptions& opts;

	vec3 pos { 0,0,4 };
	vec3 forward{ 0,0,-1 };
	double latitude { 0 };
	double longtitude{ 0 };

	mat4 viewMatrix { glm::lookAt(pos, pos + vec3(0,0,1), vec3(0, 1, 0)) };
	mat4 projMatrix { glm::perspective(radians(opts.FOV), (float)opts.width / opts.height, 0.1f, 100.0f) };

	Camera(ViewOptions& opts)
		: opts(opts)
	{}

	void processInput();

private:
	mat4 calcViewMatrix();
	void readControls();
};