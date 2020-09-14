#pragma once
#include "includes.h"

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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

class Camera
{
public:

	ViewOptions& opts;

	vec3 pos { -4.9, 6.1, 5.6 };
	vec3 forward{ 0,0,-1 };
	double latitude { -30.1/90 };
	double longtitude{ 29.7/180 };

	mat4 viewMatrix { glm::lookAt(pos, pos + vec3(0,0,-1), vec3(0, 1, 0)) };
	mat4 projMatrix { glm::perspective(radians(opts.FOV), (float)opts.width / opts.height, 0.1f, 100.0f) };

	Camera(ViewOptions& opts);
	~Camera();
	void processInput();
	static int isDown(int key);
private:
	mat4 calcViewMatrix();
	void readControls();
};