#include "includes.h"
#include "Macros.h"
#include "MonoLightShaders.h"
#include "Shaders.h"
#include "LightShaders.h"
#include "StandardModel.h"
#include "StandardModelLoader.h"
#include "TextPrinter.h"
#include "Cube.h"

#include "util/shader.hpp"
#include "util/texture.hpp"
#include "util/objloader.hpp"
#include "util/vboindexer.hpp"

ViewOptions init(ViewOptions defaults);
void printInfo(Camera& camera, TextPrinter& printer);
void drawDemoModels(StandardModel& model, Shaders& shaders);
void drawDemoPlane(StandardModel& cube, Shaders& shaders);

int main(void)
{
	ViewOptions opts;
	opts = init(opts);
	Camera camera(opts);

	TextPrinter printer("Holstein.DDS", "TextShader.vert", "TextShader.frag");
	StandardModel suzanne = StandardModelLoader::loadObjAndDDS("suzanne.obj", "uvmap.DDS");
	StandardModel cube = StandardModelLoader::loadCubeAndDDS("uvmap.DDS");

	Light light(vec3(0, 4, 0), vec3(1, 0.5, 0), 10);
	Shaders&& shaders = MonoLightShaders("MonoLightShader.vert", "MonoLightShader.frag", camera, light);
	Shaders&& lightShaders = LightShaders("LightShader.vert", "LightShader.frag", camera);

	while (glfwGetKey(opts.window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(opts.window) == 0)
	{
		newFrameDelta();
		{ /* Handle input */
			glfwPollEvents();
			{ /* Handle pausing */
				static bool paused{};
				static bool before = Camera::isDown(GLFW_KEY_P);
				bool now = Camera::isDown(GLFW_KEY_P);
				if (now != before && now)
				{
					paused = !paused;
					glfwSetInputMode(opts.window, GLFW_CURSOR, paused ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
					if (paused)
					{
						char text[] = "Paused";
						printer.print(text, 250, 300, 50);
						if (opts.doubleBuffered) glfwSwapBuffers(opts.window); else glFlush();
					} else glfwSetCursorPos(opts.window, opts.width / 2, opts.height / 2);
				} before = now;
				if (paused)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(50));
					continue;
				}
			}
			camera.processInput();
		}
		 
		{ /* Render */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glUseProgram(shaders.program);
			drawDemoModels(suzanne, shaders);
			drawDemoPlane(cube, shaders);
			glUseProgram(lightShaders.program);
			lightShaders.draw(cube, light.pos);
			printInfo(camera, printer);

			if (opts.doubleBuffered) glfwSwapBuffers(opts.window); else glFlush();
		}
	}
}

void drawDemoPlane(StandardModel& cube, Shaders& shaders)
{
	static double y[10][10];
	static bool up[10][10];
	once()
	{
		srand(0); //dont use srand()/rand()
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				y[i][j] = rand() / (float)RAND_MAX;
				up[i][j] = rand() % 2;
			}
		}
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (y[i][j] > 1) up[i][j] = false;
			if (y[i][j] < 0) up[i][j] = true;
			int modifier = up[i][j] ? 1 : -1;
			y[i][j] += modifier * getFrameDelta();
			shaders.draw(cube, vec3((float)i-5, y[i][j], (float)j-5));
		}
	}
}

void drawDemoModels(StandardModel& model, Shaders& shaders)
{
	static bool toggle{ true };

	static bool before = Camera::isDown(GLFW_KEY_F);
	bool now = Camera::isDown(GLFW_KEY_F);
	if (now != before) toggle ^= now;
	before = now;;

	if (toggle)
	{
		static float angle = 0;
		shaders.draw(model, rotate(translate(base, vec3(2, 3, 2)), angle, right));
		shaders.draw(model, rotate(translate(base, vec3(3, 7, 3)), angle, back));
		shaders.draw(model, rotate(translate(base, vec3(-3, 5, 0)), angle, up));
		angle -= (float)getFrameDelta();
	}
}

ViewOptions init(ViewOptions opts)
{
	GLFWwindow* window = nullptr;
	int width{ opts.width }, height{ opts.height };

	srand((unsigned int)time(0));
	if (!glfwInit())
		errorGLFW("glfwInit()");

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, opts.doubleBuffered);

	if (opts.fullscreen)
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		width = mode->width;
		height = mode->height;
		window = glfwCreateWindow(width, height, "DEMO", monitor, NULL);
	} else
	{
		window = glfwCreateWindow(width, height, "DEMO", NULL, NULL);
	}

	if (!window)
		errorGLFW("glfwCreateWindow()");
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glewExperimental = true;
	GLenum code = glewInit();
	if (code != GLEW_OK)
		errorGLEW("glewInit()", code);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwPollEvents(); // so the below line will work
	glfwSetCursorPos(window, width / 2, height / 2);

	glClearColor(0.05f, 0.0f, 0.05f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	opts.width = width;
	opts.height = height;
	opts.window = window;
	return opts;
}

void printInfo(Camera& camera, TextPrinter& printer)
{
	char text[0x20];
	sprintf(text, "%.f FPS", fps());
	printer.print(text, 5, 10, 20);

	sprintf(text, "FoV: %.f°", camera.opts.FOV);
	printer.print(text, 610, 570, 20);

	sprintf(text, "%+.1fx, %+.1fy, %+.1fz", camera.forward.x, camera.forward.y, camera.forward.z);
	printer.print(text, 5, 570, 20);
	sprintf(text, "(%+.1f°, %+.1f°)", camera.latitude * 90, camera.longtitude * 180);
	printer.print(text, 5, 540, 20);

	sprintf(text, "%+.1fx", camera.pos.x);
	printer.print(text, 700, 50, 20);
	sprintf(text, "%+.1fy", camera.pos.y);
	printer.print(text, 700, 30, 20);
	sprintf(text, "%+.1fz", camera.pos.z);
	printer.print(text, 700, 10, 20);
}