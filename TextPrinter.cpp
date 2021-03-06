#include "TextPrinter.h"
#include "util/texture.hpp"
#include "util/shader.hpp"

TextPrinter::TextPrinter(const char* texturePath, const char* vertexShader, const char* fragmentShader)
{
	glGenBuffers(1, &vertexBuf);
	glGenBuffers(1, &uvBuf);

	fontAtlas = loadDDS(texturePath);
	program = LoadShaders(vertexShader, fragmentShader);
	uniFontAtlas = glGetUniformLocation(program, "fontAtlas");
}

void TextPrinter::print(const char* text, int x, int y, int size)
{
	size_t length = strlen(text);

	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> UVs;
	for (unsigned int i = 0; i < length; i++)
	{

		glm::vec2 vertex_up_left = glm::vec2(x + i * size, y + size);
		glm::vec2 vertex_up_right = glm::vec2(x + i * size + size, y + size);
		glm::vec2 vertex_down_right = glm::vec2(x + i * size + size, y);
		glm::vec2 vertex_down_left = glm::vec2(x + i * size, y);

		vertices.push_back(vertex_up_left);
		vertices.push_back(vertex_down_left);
		vertices.push_back(vertex_up_right);

		vertices.push_back(vertex_down_right);
		vertices.push_back(vertex_up_right);
		vertices.push_back(vertex_down_left);

		char character = text[i];
		float uv_x = (character % 16) / 16.0f;
		float uv_y = (character / 16) / 16.0f;

		glm::vec2 uv_up_left = glm::vec2(uv_x, uv_y);
		glm::vec2 uv_up_right = glm::vec2(uv_x + 1.0f / 16.0f, uv_y);
		glm::vec2 uv_down_right = glm::vec2(uv_x + 1.0f / 16.0f, (uv_y + 1.0f / 16.0f));
		glm::vec2 uv_down_left = glm::vec2(uv_x, (uv_y + 1.0f / 16.0f));
		UVs.push_back(uv_up_left);
		UVs.push_back(uv_down_left);
		UVs.push_back(uv_up_right);

		UVs.push_back(uv_down_right);
		UVs.push_back(uv_up_right);
		UVs.push_back(uv_down_left);
	}
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuf);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuf);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);

	GLint oProgram;
	glGetIntegerv(GL_CURRENT_PROGRAM, &oProgram);
	glUseProgram(program);

	glBindTexture(GL_TEXTURE_2D, fontAtlas);
	glUniform1i(uniFontAtlas, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuf);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuf);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	int wasEnabled = glIsEnabled(GL_BLEND);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices.size());

	glUseProgram(oProgram);
	if (!wasEnabled) glDisable(GL_BLEND);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

TextPrinter::~TextPrinter()
{
	puts("~TextPrinter()");
	glDeleteBuffers(1, &vertexBuf);
	glDeleteBuffers(1, &uvBuf);
	glDeleteTextures(1, &fontAtlas);
	glDeleteProgram(program);
}