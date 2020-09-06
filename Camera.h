#pragma once
#include "includes.h"
class Camera
{
	GLFWwindow* window;

	vec3 pos { 0,0,4 };
	vec3 forward{ 0,0,-1 };
	double latitude { 0 };
	double longtitude{ 0 };

	mat4 viewMatrix { glm::lookAt(pos, pos + vec3(0,0,1), vec3(0, 1, 0)) };
	mat4 projMatrix { glm::perspective(radians((float)G.FOV), (float)G.width / G.height, 0.1f, 100.0f) };
	
public:

	mat4 getViewMatrix() { return viewMatrix; }
	mat4 getProjMatrix() { return projMatrix; }

	Camera(GLFWwindow* window)
		: window(window)
	{}

	void processInput();

private:
	mat4 calcViewMatrix();
	void readControls();
};