#pragma once
#include "Model.h"
#include "includes.h"

class Cube : Model
{
	static bool alive;
	static Cube c;

	static GLsizei numIndices_;

	static GLuint vertexArray_;
	static GLuint elementBuf_;
	static GLuint vertexBuf_;
	static GLuint uvBuf_;
	static GLuint normalBuf_;
public:
	static Cube& get()
	{
		if (!alive) throw "Accessing cube outside of its lifetime"; 
		return c;
	}

	GLsizei numIndices() { return numIndices_; }
	GLuint vertexArray() { return vertexArray_; }
	GLuint elementBuf() { return elementBuf_; }
	GLuint vertexBuf() { return vertexBuf_; }
	GLuint uvBuf() { return uvBuf_; }
	GLuint normalBuf() { return normalBuf_; }

	Cube();
	~Cube();
};

/* What the fuck is this pattern? Well, its a singleton BUT it has an automatic scope BUT it doesn't have to be passed around.*/