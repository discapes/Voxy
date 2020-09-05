#pragma once
#include "Camera.h"
#include "Shaders.h"

class Game
{
public:
	Camera* camera;
	Shaders* shaders;
	GLFWwindow* window;
	Game(Shaders* shaders);
	~Game();
};