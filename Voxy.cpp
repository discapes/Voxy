#include "includes.h"
#include "Macros.h"
#include "StandardShaders.h"
#include "TextPrinter.h"
#include "Cube.h"

#include "util/shader.hpp"
#include "util/texture.hpp"
#include "util/objloader.hpp"
#include "util/vboindexer.hpp"

ViewOptions init(ViewOptions defaults);
void printInfo(Camera& camera, TextPrinter& printer);
void drawThreeModels(Model& model, Shaders& shaders);

int main(void)
{
	ViewOptions opts;
	opts = init(opts);
	Camera camera(opts);
	Shaders&& shaders = StandardShaders("StandardShader.vert", "StandardShader.frag", camera);
	TextPrinter printer("Holstein.DDS", "TextShader.vert", "TextShader.frag");
	Model suzanne("suzanne.obj", "uvmap.DDS");
	Cube cube;
	glUseProgram(shaders.program);
	do
	{
		newFrameDelta();
		glfwPollEvents();
		{
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

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawThreeModels(suzanne, shaders);
		static float angle = 0;
		shaders.drawCube(rotate(translate(base, vec3(0, 0, 0)), angle, x));
		shaders.drawCube(rotate(translate(base, vec3(3, 0, 0)), angle, y));
		shaders.drawCube(rotate(translate(base, vec3(-3, 0, 0)), angle, z));
		shaders.drawCube(vec3(0, 0, 0));
		angle -= (float)getFrameDelta();
		printInfo(camera, printer);

		if (opts.doubleBuffered) glfwSwapBuffers(opts.window); else glFlush();
	}
	while (glfwGetKey(opts.window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(opts.window) == 0);
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

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
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

	sprintf(text, "FoV: %.f�", camera.opts.FOV);
	printer.print(text, 610, 570, 20);

	sprintf(text, "%+.1fx, %+.1fy, %+.1fz", camera.forward.x, camera.forward.y, camera.forward.z);
	printer.print(text, 5, 570, 20);
	sprintf(text, "(%+.1f�, %+.1f�)", camera.latitude * 90, camera.longtitude * 180);
	printer.print(text, 5, 540, 20);

	sprintf(text, "%+.1fx", camera.pos.x);
	printer.print(text, 700, 50, 20);
	sprintf(text, "%+.1fy", camera.pos.y);
	printer.print(text, 700, 30, 20);
	sprintf(text, "%+.1fz", camera.pos.z);
	printer.print(text, 700, 10, 20);
}

void drawThreeModels(Model& model, Shaders& shaders)
{
	static float angle = 0;

	static bool altTransform{};
	
	static bool before = Camera::isDown(GLFW_KEY_F);
	bool now = Camera::isDown(GLFW_KEY_F);
	if (now != before) altTransform ^= now;
	before = now;

	if (altTransform)
	{
		shaders.draw(model, rotate(translate(base, vec3(0, 0, 0)), angle, x));
		shaders.draw(model, rotate(translate(base, vec3(3, 0, 0)), angle, y));
		shaders.draw(model, rotate(translate(base, vec3(-3, 0, 0)), angle, z));
	} else
	{
		shaders.draw(model, translate(rotate(base, angle, x), vec3(0, 0, 0)));
		shaders.draw(model, translate(rotate(base, angle, y), vec3(3, 0, 0)));
		shaders.draw(model, translate(rotate(base, angle, z), vec3(-3, 0, 0)));
	}
	angle -= (float)getFrameDelta();
}