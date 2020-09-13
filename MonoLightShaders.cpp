#include "MonoLightShaders.h"
#include "Light.h"
#include "util/shader.hpp"
#include "Cube.h"

MonoLightShaders::MonoLightShaders(const char* vertexShaderName, const char* fragmentShaderName, const Camera& camera, const Light& light)
	: vertexShaderName(vertexShaderName),
	fragmentShaderName(fragmentShaderName),
	camera(camera),
	light(light)
{
	program = LoadShaders(vertexShaderName, fragmentShaderName);	
	if (program == NULL) std::exit(1);
	uniLightPos = glGetUniformLocation(program, "lightPos");
	uniMVP = glGetUniformLocation(program, "MVP");
	uniM = glGetUniformLocation(program, "M");
	uniV = glGetUniformLocation(program, "V");
	uniTex = glGetUniformLocation(program, "tex");
	uniLightColor = glGetUniformLocation(program, "lightColor");
}

MonoLightShaders::~MonoLightShaders()
{
	puts("~MonoLightShaders()");
	glDeleteProgram(program);
}

void MonoLightShaders::draw(const Model& model, const mat4& modelMatrix)
{
	glm::mat4 MVP = camera.projMatrix * camera.viewMatrix * modelMatrix;

	glUniformMatrix4fv(uniMVP, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(uniM, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(uniV, 1, GL_FALSE, &camera.viewMatrix[0][0]);

	glUniform3f(uniLightColor, light.color.x, light.color.y, light.color.z);
	glUniform3f(uniLightPos, light.pos.x, light.pos.y, light.pos.z);

	glBindTexture(GL_TEXTURE_2D, model.texture);
	glUniform1i(uniTex, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, model.vertexBuf);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, model.uvBuf);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, model.normalBuf);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.elementBuf);

	glDrawElements(GL_TRIANGLES, (GLsizei)model.numIndices, GL_UNSIGNED_SHORT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}