#include "Cube.h"

GLsizei Cube::numIndices;

GLuint Cube::vertexArray;
GLuint Cube::elementBuf;
GLuint Cube::vertexBuf;
GLuint Cube::uvBuf;
GLuint Cube::normalBuf;


static vec2 uvs[24]
{
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
};

static vec3 normals[24]
{
	{ -1, 0, 0 },
	{ 0, -1, 0 },
	{ 0, 0, -1 },

	{ 1, 0, 0 },
	{ 0, -1, 0 },
	{ 0, 0, -1 },

	{ 1, 0, 0 },
	{ 0, 1, 0 },
	{ 0, 0, -1 },

	{ 1, 0, 0 },
	{ 0, 1, 0 },
	{ 0, 0, 1 },

	{ -1, 0, 0 },
	{ 0, 1, 0 },
	{ 0, 0, 1 },

	{ -1, 0, 0 },
	{ 0, -1, 0 },
	{ 0, 0, 1 },

	{ 1, 0, 0 },
	{ 0, -1, 0 },
	{ 0, 0, 1 },

	{ -1, 0, 0 },
	{ 0, 1, 0 },
	{ 0, 0, -1 },
};

static vec3 vertices[24]
{
	{ -0.5, -0.5, -0.5 },
	{ -0.5, -0.5, -0.5 },
	{ -0.5, -0.5, -0.5 },

	{ 0.5, -0.5, -0.5 },
	{ 0.5, -0.5, -0.5 },
	{ 0.5, -0.5, -0.5 },

	{ 0.5, 0.5, -0.5 },
	{ 0.5, 0.5, -0.5 },
	{ 0.5, 0.5, -0.5 },

	{ 0.5, 0.5, 0.5 },
	{ 0.5, 0.5, 0.5 },
	{ 0.5, 0.5, 0.5 },

	{ -0.5, 0.5, 0.5 },
	{ -0.5, 0.5, 0.5 },
	{ -0.5, 0.5, 0.5 },

	{ -0.5, -0.5, 0.5 },
	{ -0.5, -0.5, 0.5 },
	{ -0.5, -0.5, 0.5 },

	{ 0.5, -0.5, 0.5 },
	{ 0.5, -0.5, 0.5 },
	{ 0.5, -0.5, 0.5 },

	{ -0.5, 0.5, -0.5 },
	{ -0.5, 0.5, -0.5 },
	{ -0.5, 0.5, -0.5 },
};

#define x *3+0
#define y *3+1
#define z *3+2
static unsigned short indices[36]
{
	0 x, 7 x, 4 x,
	4 x, 5 x, 0 x,

	1 z, 2 z, 7 z,
	7 z, 0 z, 1 z,

	6 x, 3 x, 2 x,
	2 x, 1 x, 6 x,

	5 z, 4 z, 3 z,
	3 z, 6 z, 5 z,

	7 y, 2 y, 3 y,
	3 y, 4 y, 7 y,

	0 y, 5 y, 6 y,
	6 y, 1 y, 0 y,
};
#undef x
#undef y
#undef z

Cube::Cube()
{
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glGenBuffers(1, &vertexBuf);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &uvBuf);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

	glGenBuffers(1, &normalBuf);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals),normals, GL_STATIC_DRAW);

	glGenBuffers(1, &elementBuf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	numIndices = sizeof(indices);
}

Cube::~Cube()
{
	puts("~Cube()");
	glDeleteBuffers(1, &vertexBuf);
	glDeleteBuffers(1, &uvBuf);
	glDeleteBuffers(1, &normalBuf);
	glDeleteBuffers(1, &elementBuf);
	glDeleteVertexArrays(1, &vertexArray);
}