#include "includes.h"
#include "TextPrinter.h"
#include "Camera.h"

#pragma warning ( disable : 4244 )

void Camera::processInput()
{
	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	double delta = currentTime - lastTime;

	calcMovement(delta);
	viewMatrix = calcViewMatrix();

	lastTime = currentTime;
}

void Camera::calcMovement(double delta)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		pos.y += G.moveSpeed * delta;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		pos.y -= G.moveSpeed * delta;

	double magnitude = sqrt(lookDirection.x * lookDirection.x + lookDirection.z * lookDirection.z);
	vec3 lookDirFlat = vec3(lookDirection.x / magnitude, 0, lookDirection.z / magnitude);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		pos.x += (lookDirFlat.x * G.moveSpeed) * delta;
		pos.z += (lookDirFlat.z * G.moveSpeed) * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		pos.x -= (lookDirFlat.x * G.moveSpeed) * delta;
		pos.z -= (lookDirFlat.z * G.moveSpeed) * delta;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		pos.x += (lookDirFlat.z * G.moveSpeed) * delta;
		pos.z += (-lookDirFlat.x * G.moveSpeed) * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		pos.x -= (lookDirFlat.z * G.moveSpeed) * delta;
		pos.z -= (-lookDirFlat.x * G.moveSpeed) * delta;
	}
}

mat4 Camera::calcViewMatrix()
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwSetCursorPos(window, G.width / 2, G.height / 2);
	latitude += G.lookSpeed * 0.005 * (G.height / 2 - ypos);
	longtitude += G.lookSpeed * 0.005 * -(G.width / 2 - xpos);
	latitude = clamp(latitude, -.999, .999);
	longtitude = longtitude < -1. ? 1. : (longtitude > 1. ? -1. : longtitude);

	double latRadians = latitude * half_pi<double>(); // radians in circle = 2pi, 1/4 circle = half_pi, so you can look 90 degrees up or down
	double longRadians = longtitude * pi<double>();

	lookDirection = vec3(
		sin(longRadians) * cos(latRadians),
		sin(latRadians),
		-cos(latRadians) * cos(longRadians)
	);

	char text[256];
	sprintf(text, "%+.1f, %+.1f, %+.1f", lookDirection.x, lookDirection.y, lookDirection.z);
	printer->print(text, 10, 450, 20);
	return glm::lookAt(pos, pos + lookDirection, vec3(0,1,0));
}