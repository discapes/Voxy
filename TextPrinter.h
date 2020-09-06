#pragma once
#include "includes.h"

class TextPrinter
{
	GLuint program;
	GLuint fontAtlas;

	GLuint uniFontAtlas;

	GLuint vertexBuf;
	GLuint uvBuf;

public:
	TextPrinter(const char* texturePath, const char* vertexShader, const char* fragmentShader);
	void print(const char* text, int x, int y, int size);
	~TextPrinter();
};