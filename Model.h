#pragma once
#include "includes.h"
#include "util/objloader.hpp"
#include "util/texture.hpp"
#include "Camera.h"

struct Model
{
	GLsizei numIndices;

	GLuint vertexArray;
	GLuint elementBuf;
	GLuint vertexBuf;
	GLuint uvBuf;
	GLuint normalBuf;
	GLuint texture;

	Model(const char* objName, const char* textureDDS);
	~Model();
};