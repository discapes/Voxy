#pragma once
#include "includes.h"

struct StandardModel
{
	GLsizei numIndices;
	GLuint vertexArray;
	GLuint elementBuf;
	GLuint vertexBuf;
	GLuint uvBuf;
	GLuint normalBuf;
	GLuint texture;

	~StandardModel()
	{
		puts("~StandardModel()");
		glDeleteBuffers(1, &vertexBuf);
		glDeleteBuffers(1, &uvBuf);
		glDeleteBuffers(1, &normalBuf);
		glDeleteBuffers(1, &elementBuf);
		glDeleteTextures(1, &texture);
		glDeleteVertexArrays(1, &vertexArray);
	}
};