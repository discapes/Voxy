#include "StandardShaders.h"
#include "util/shader.hpp"

void StandardShaders::build()
{
	program = LoadShaders(vertexShaderName, fragmentShaderName);
	uniLightPos = glGetUniformLocation(program, "lightPos");
	uniMVP = glGetUniformLocation(program, "MVP");
	uniM = glGetUniformLocation(program, "M");
	uniV = glGetUniformLocation(program, "V");
	uniTex = glGetUniformLocation(program, "tex");
	uniLightColor = glGetUniformLocation(program, "lightColor");
}

StandardShaders::~StandardShaders()
{
	puts("~StandardShaders()");
	glDeleteProgram(program);
}

void StandardShaders::draw(Model& model, Camera* camera, mat4 modelMatrix)
{
	glUseProgram(program);

	glm::mat4 M = modelMatrix;
	glm::mat4 V = camera->getViewMatrix();
	glm::mat4 P = camera->getProjMatrix();
	glm::mat4 MVP = P * V * M;

	glUniformMatrix4fv(uniMVP, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(uniM, 1, GL_FALSE, &M[0][0]);
	glUniformMatrix4fv(uniV, 1, GL_FALSE, &V[0][0]);

	glUniform3f(uniLightColor, lightColor.x, lightColor.y, lightColor.z);
	glUniform3f(uniLightPos, lightPos.x, lightPos.y, lightPos.z);

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