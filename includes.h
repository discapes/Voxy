#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
#include "Settings.h"

inline void errorGLFW(const char* whatFailed)
{
	const char* error;
	glfwGetError(&error);
	std::printf("%s failed: %s", whatFailed, error);
	glfwTerminate();
	std::exit(1);
}

inline void errorGLEW(const char* whatFailed, GLenum error)
{
	std::printf("%s failed: %s", whatFailed, glewGetErrorString(error));
	glfwTerminate();
	std::exit(1);
}

template <typename T>
inline size_t vecSize(const std::vector<T>& vec)
{
	return vec.size() * sizeof(T);
}