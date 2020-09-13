#include "LightShaders.h"
#include "Light.h"
#include "util/shader.hpp"
#include "Cube.h"

LightShaders::LightShaders(const char* vertexShaderName, const char* fragmentShaderName, const Camera& camera)
	: camera(camera)
{
	program = LoadShaders(vertexShaderName, fragmentShaderName);
	if (program == NULL) std::exit(1);
	uniMVP = glGetUniformLocation(program, "MVP");
	uniTex = glGetUniformLocation(program, "tex");
}

LightShaders::~LightShaders()
{
	puts("~LightShaders()");
	glDeleteProgram(program);
}

void LightShaders::draw(const StandardModel& model, const mat4& modelMatrix)
{
	glm::mat4 MVP = camera.projMatrix * camera.viewMatrix * modelMatrix;

	glUniformMatrix4fv(uniMVP, 1, GL_FALSE, &MVP[0][0]);

	glBindTexture(GL_TEXTURE_2D, model.texture);
	glUniform1i(uniTex, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, model.vertexBuf);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, model.uvBuf);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.elementBuf);

	glDrawElements(GL_TRIANGLES, (GLsizei)model.numIndices, GL_UNSIGNED_SHORT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}