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
	Game game(new StandardShaders("StandardShader.vert", "StandardShader.frag", new Camera(window)));

	printer = new TextPrinter("Holstein.DDS", "TextShader.vert", "TextShader.frag");

	Model suzanne("suzanne.obj", "uvmap.DDS");

	do
	{
		game.calcFrameDelta();
		glfwPollEvents();
		game.camera->processInput();



		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50)); // artificial lag




		if (G.doubleBuffered) glfwSwapBuffers(game.window); else glFlush();
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

void printText(Camera* camera)
{
	char text[0x10];
	sprintf(text, "%.f FPS", fps());
	printer->print(text, 5, 10, 20);

	char text[0x20];
	sprintf(text, "%+.1fx, %+.1fy, %+.1fz", camera->forward.x, camera->forward.y, camera->forward.z);
	printer->print(text, 5, 570, 20);
	sprintf(text, "(%+.1f°, %+.1f°)", camera->latitude * 90, camera->longtitude * 180);
	printer->print(text, 5, 540, 20);

	sprintf(text, "%+.1fx", camera->pos.x);
	printer->print(text, 700, 50, 20);
	sprintf(text, "%+.1fy", camera->pos.y);
	printer->print(text, 700, 30, 20);
	sprintf(text, "%+.1fz", camera->pos.z);
	printer->print(text, 700, 10, 20);
}

void renderThreeModels(Model* model, Shaders* shaders)
{
	glUseProgram(shaders->program);

	static float angle = 0;
	static vec3 x(1, 0, 0);
	static vec3 y(0, 1, 0);
	static vec3 z(0, 0, 1);
	static mat4 identity(1);
	if (true)
	{
		shaders->draw(model, game.camera, rotate(translate(identity, vec3(0, 0, 0)), angle, x));
		shaders->draw(model, game.camera, rotate(translate(identity, vec3(3, 0, 0)), angle, y));
		shaders->draw(model, game.camera, rotate(translate(identity, vec3(-3, 0, 0)), angle, z));
	} else
	{
		shaders->draw(model, game.camera, translate(rotate(identity, angle, x), vec3(0, 0, 0)));
		shaders->draw(model, game.camera, translate(rotate(identity, angle, y), vec3(3, 0, 0)));
		shaders->draw(model, game.camera, translate(rotate(identity, angle, z), vec3(-3, 0, 0)));
	}
	angle -= (float)G.frameDelta;
}