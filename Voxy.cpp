#include "includes.h"
#include "Shaders.h"
#include "Game.h"
#include "StandardShaders.h"
#include "TextPrinter.h"

#include "util/shader.hpp"
#include "util/texture.hpp"
#include "util/objloader.hpp"
#include "util/vboindexer.hpp"

double fps();

TextPrinter* printer;

int main(void)
{
	Game game(new StandardShaders("StandardShader.vert", "StandardShader.frag"));

	printer = new TextPrinter("Holstein.DDS", "TextShader.vert", "TextShader.frag");

	Model suzanne("suzanne.obj", "uvmap.DDS");

	do
	{
		game.calcFrameDelta();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		static float angle = 0;
		if (true)
		{
			game.shaders->draw(suzanne, game.camera, rotate(translate(mat4(1), vec3(0, 0, 0)), angle, vec3(1, 0, 0)));
			game.shaders->draw(suzanne, game.camera, rotate(translate(mat4(1), vec3(3, 0, 0)), angle, vec3(0, 1, 0)));
			game.shaders->draw(suzanne, game.camera, rotate(translate(mat4(1), vec3(-3, 0, 0)), angle, vec3(0, 0, 1)));
		} else
		{
			game.shaders->draw(suzanne, game.camera, translate(rotate(mat4(1), angle, vec3(1, 0, 0)), vec3(0, 0, 0)));
			game.shaders->draw(suzanne, game.camera, translate(rotate(mat4(1), angle, vec3(0, 1, 0)), vec3(3, 0, 0)));
			game.shaders->draw(suzanne, game.camera, translate(rotate(mat4(1), angle, vec3(0, 0, 1)), vec3(-3, 0, 0)));
		}
		angle -= G.frameDelta;

		//std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50)); // artificial lag
		char text[0x10];
		sprintf(text, "%.f FPS", fps());
		printer->print(text, 5, 10, 20);

		game.camera->processInput();

		glfwSwapBuffers(game.window);
		glfwPollEvents();
	}
	while (glfwGetKey(game.window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(game.window) == 0);

	delete printer;
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