#pragma once
#include "includes.h"

void errorGLFW(const char* whatFailed);
void errorGLEW(const char* whatFailed, GLenum error);
template <typename T>
size_t vecSize(const std::vector<T>& vec);
double getFrameDelta();
void newFrameDelta();
double fps();

#define ifEvent(value, doIf, doElse)	\
{ static bool event = true;				\
if (value)								\
{ doIf; event = false;					\
} else { doElse; event = true; } }		\

#define ifKeyEvent(key, doIf, doElse)		\
ifEvent(Camera::isDown(key), doIf, doElse)	\

// event, more like notPressedLastTime
struct ViewOptions
{
	bool fullscreen = false;
	bool doubleBuffered = true;

	GLFWwindow* window;
	double lookSpeed = 1;
	double moveSpeed = 3;
	float FOV = 110;

	int width = 1024;
	int height = 768;
};
