#pragma once
#include "includes.h"

class Cube
{
public:
	static GLsizei numIndices;

	static GLuint vertexArray;
	static GLuint elementBuf;
	static GLuint vertexBuf;
	static GLuint uvBuf;
	static GLuint normalBuf;

	Cube();
	~Cube();
};