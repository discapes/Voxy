#pragma once
#include "includes.h"

void errorGLFW(const char* whatFailed);
void errorGLEW(const char* whatFailed, GLenum error);
template <typename T>
size_t vecSize(const std::vector<T>& vec);
double getFrameDelta();
void newFrameDelta();
double fps();

// event, more like notPressedLastTime
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

static vec3 x(1, 0, 0);
static vec3 y(0, 1, 0);
static vec3 z(0, 0, 1);
static mat4 base(1);
