#include "includes.h"

void errorGLFW(const char* whatFailed)
{
	const char* error;
	glfwGetError(&error);
	std::printf("%s failed: %s", whatFailed, error);
	glfwTerminate();
	std::exit(1);
}

void errorGLEW(const char* whatFailed, GLenum error)
{
	std::printf("%s failed: %s", whatFailed, glewGetErrorString(error));
	glfwTerminate();
	std::exit(1);
}

template <typename T>
size_t vecSize(const std::vector<T>& vec)
{
	return vec.size() * sizeof(T);
}

double frameDelta = 0;
double getFrameDelta()
{
	return frameDelta;
}

void newFrameDelta()
{
	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	frameDelta = currentTime - lastTime;

	lastTime = currentTime;
}

double fps()
{
	static double fps;

	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();

	static int nbFrames = 0;

	if (currentTime - lastTime >= 1.0)
	{
		fps = nbFrames;
		nbFrames = 0;
		lastTime = currentTime;
	}
	nbFrames++;
	return fps;
}