#pragma once
#include "includes.h"

void errorGLFW(const char* whatFailed);
void errorGLEW(const char* whatFailed, GLenum error);
template <typename T>
size_t vecSize(const std::vector<T>& vec);
double getFrameDelta();
void newFrameDelta();
double fps();

struct ViewOptions
{
	bool fullscreen = true;
	bool doubleBuffered = false;

	GLFWwindow* window;
	double lookSpeed = 1;
	double moveSpeed = 3;
	float FOV = 110;

	int width = 1024;
	int height = 768;
};

