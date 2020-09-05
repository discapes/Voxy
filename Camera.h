#pragma once
#include "includes.h"
class Camera
{
	GLFWwindow* window;

	double lookSpeed = 1;
	double moveSpeed = 2;
	int FOV = 90;

	vec3 pos { 0,0,4 };
	vec3 lookDirection{ 0,0,-1 };
	double latitude { 0 };
	double longtitude{ 0 };

	mat4 viewMatrix { glm::lookAt(pos, pos + lookDirection, vec3(0, 1, 0)) };
	mat4 projMatrix { glm::perspective(radians((float)FOV), (float)width / height, 0.1f, 100.0f) };
	
public:

	mat4 getViewMatrix() { return viewMatrix; }
	mat4 getProjMatrix() { return projMatrix; }

	Camera(GLFWwindow* window)
		: window(window)
	{}

	void processInput();

private:
	void calcLookDirection();
	void calcMovement(double timeDelta);
};