#pragma once
#include "includes.h"

void errorGLFW(const char* whatFailed);
void errorGLEW(const char* whatFailed, GLenum error);
template <typename T>
size_t vecSize(const std::vector<T>& vec);
double getFrameDelta();
void newFrameDelta();
double fps();

#define once() \
	static bool done{}; if (!done && (done = true))

static vec3 right(1, 0, 0);
static vec3 up(0, 1, 0);
static vec3 back(0, 0, 1);
static mat4 base(1);
