#include "includes.h"
#include "Camera.h"

#pragma warning ( disable : 4244 )

void Camera::processInput()
{
	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	double delta = currentTime - lastTime;

	calcMovement(delta);
	calcLookDirection();

	viewMatrix = glm::lookAt(pos, pos + lookDirection, vec3(0,1,0));

	lastTime = currentTime;
}

void Camera::calcMovement(double delta)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		pos.y += moveSpeed * delta;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		pos.y -= moveSpeed * delta;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		pos.x += (lookDirection.x * moveSpeed) * delta;
		pos.z += (lookDirection.z * moveSpeed) * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		pos.x -= (lookDirection.x * moveSpeed) * delta;
		pos.z -= (lookDirection.z * moveSpeed) * delta;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		pos.x += (lookDirection.z * moveSpeed) * delta;
		pos.z += (-lookDirection.x * moveSpeed) * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		pos.x -= (lookDirection.z * moveSpeed) * delta;
		pos.z -= (-lookDirection.x * moveSpeed) * delta;
	}
}

void Camera::calcLookDirection()
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwSetCursorPos(window, width / 2, height / 2);
	latitude += lookSpeed * 0.005 * (height / 2 - ypos);
	longtitude += lookSpeed * 0.005 * -(width / 2 - xpos);
	latitude = clamp(latitude, -1., 1.);
	longtitude = longtitude < -1. ? 1. : (longtitude > 1. ? -1. : longtitude);

	double latRadians = latitude * half_pi<double>(); // radians in circle = 2pi, 1/4 circle = half_pi, so you can look 90 degrees up or down
	double longRadians = longtitude * pi<double>();
	lookDirection = vec3(
		sin(longRadians),
		sin(latRadians),
		-cos(latRadians) * cos(longRadians)
	);
}