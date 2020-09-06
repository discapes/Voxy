#include "includes.h"
#include "Macros.h"
#include "Camera.h"

#pragma warning ( disable : 4244 )

static Camera* instance;

Camera::Camera(ViewOptions& opts) 
	: opts(opts)
{
	instance = this;
	glfwSetScrollCallback(opts.window, scroll_callback);
}

Camera::~Camera()
{
	puts("~Camera()");
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	ViewOptions& opts = instance->opts;
	opts.FOV -= (float)yoffset;
	opts.FOV = clamp(opts.FOV, 60.f, 160.f);
	instance->projMatrix = glm::perspective(radians(opts.FOV), (float)opts.width / opts.height, 0.1f, 100.0f);
}

int Camera::getKey(int key)
{
	return glfwGetKey(instance->opts.window, key);
}

void Camera::processInput()
{
	readControls();
	viewMatrix = calcViewMatrix();
}

void Camera::readControls()
{
	// my pet peeve
	GLFWwindow* window = opts.window;
	int width = opts.width;
	int height = opts.height;
	double moveSpeed = opts.moveSpeed;
	double frameDelta = getFrameDelta();

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwSetCursorPos(window, width / 2, height / 2);
	latitude += opts.lookSpeed * 0.005 * (height / 2 - ypos);
	longtitude += opts.lookSpeed * 0.005 * -(width / 2 - xpos);
	latitude = clamp(latitude, -1., 1.);
	longtitude = longtitude < -1. ? 1. : (longtitude > 1. ? -1. : longtitude);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		pos.y += moveSpeed * frameDelta;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		pos.y -= moveSpeed * frameDelta;

	double magnitude = sqrt(forward.x * forward.x + forward.z * forward.z);
	vec3 lookDirFlat = vec3(forward.x / magnitude, 0, forward.z / magnitude);
	vec3 delta(0,0,0);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		delta.x += (lookDirFlat.x * moveSpeed) * frameDelta;
		delta.z += (lookDirFlat.z * moveSpeed) * frameDelta;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		delta.x -= (lookDirFlat.x * moveSpeed) * frameDelta;
		delta.z -= (lookDirFlat.z * moveSpeed) * frameDelta;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		delta.x += (lookDirFlat.z * moveSpeed) * frameDelta;
		delta.z += (-lookDirFlat.x * moveSpeed) * frameDelta;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		delta.x -= (lookDirFlat.z * moveSpeed) * frameDelta;
		delta.z -= (-lookDirFlat.x * moveSpeed) * frameDelta;
	}
	normalize(delta);
	pos += delta;
}

mat4 Camera::calcViewMatrix()
{
	double latRadians = latitude * half_pi<double>(); // radians in circle = 2pi, 1/4 circle = half_pi, so you can look 90 degrees up or down
	double longRadians = longtitude * pi<double>();

	double sinLong = sin(longRadians);
	double cosLong = cos(longRadians);
	double sinLat = sin(latRadians);
	double cosLat = cos(latRadians);

	forward = vec3(
		sinLong * cosLat,
		sinLat,
		-cosLat * cosLong
	);

	vec3 up = vec3( // @Discape next step is to take advantage of the fact that sin(x + pi / 2) = cos(x) and cos(x + pi / 2) = -sin(x) and make it so that you only compute all these sines and cosines once
		sinLong * -sinLat,
		cosLat,
		sinLat * cosLong
	);
	return glm::lookAt(pos, pos + forward, up);
}