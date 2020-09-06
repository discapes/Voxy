#include "includes.h"
#include "Game.h"

Game::Game(Shaders* shaders)
	: shaders(shaders)
{
	srand((unsigned int)time(0));
	if (!glfwInit())
		errorGLFW("glfwInit()");

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (G.fullscreen)
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		G.width = mode->width;
		G.height = mode->height;
		window = glfwCreateWindow(G.width, G.height, "DEMO", monitor, NULL);
	} else
	{
		window = glfwCreateWindow(G.width, G.height, "DEMO", NULL, NULL);
	}


	if (!window)
		errorGLFW("glfwCreateWindow()");
	glfwMakeContextCurrent(window);

	glewExperimental = true;
	GLenum code = glewInit();
	if (code != GLEW_OK)
		errorGLEW("glewInit()", code);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwPollEvents(); // so the below line will work
	glfwSetCursorPos(window, G.width / 2, G.height / 2);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	camera = new Camera(window);
	shaders->build();
}

Game::~Game()
{
	puts("~Game()");
	delete camera;
	delete shaders;
	glfwTerminate();
}