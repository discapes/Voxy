#include "Cube.h"

bool Cube::alive = false;
Cube Cube::c;

GLsizei Cube::numIndices_;

GLuint Cube::vertexArray_;
GLuint Cube::elementBuf_;
GLuint Cube::vertexBuf_;
GLuint Cube::uvBuf_;
GLuint Cube::normalBuf_;

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

/*
Wieku: You treat z=-0.5 as being closer to the camera, if you treat z=-0.5 as being farther from it (which you should, camera looks at negative z)
	then you can notice that triangle {0 7 4} is CW
	Flip z coordinate in box vertices and it should work
*/

static vec3 vertices[24]
{
	{ -0.5, -0.5, 0.5 },
	{ -0.5, -0.5, 0.5 },
	{ -0.5, -0.5, 0.5 },

	{ 0.5, -0.5, 0.5 },
	{ 0.5, -0.5, 0.5 },
	{ 0.5, -0.5, 0.5 },

	{ 0.5, 0.5, 0.5 },
	{ 0.5, 0.5, 0.5 },
	{ 0.5, 0.5, 0.5 },

	{ 0.5, 0.5, -0.5 },
	{ 0.5, 0.5, -0.5 },
	{ 0.5, 0.5, -0.5 },

	{ -0.5, 0.5, -0.5 },
	{ -0.5, 0.5, -0.5 },
	{ -0.5, 0.5, -0.5 },

	{ -0.5, -0.5, -0.5 },
	{ -0.5, -0.5, -0.5 },
	{ -0.5, -0.5, -0.5 },

	{ 0.5, -0.5, -0.5 },
	{ 0.5, -0.5, -0.5 },
	{ 0.5, -0.5, -0.5 },

	{ -0.5, 0.5, 0.5 },
	{ -0.5, 0.5, 0.5 },
	{ -0.5, 0.5, 0.5 },
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
	if (alive) throw "Cube should be created only once!";
	alive = true;

	glGenVertexArrays(1, &c.vertexArray_);
	glBindVertexArray(c.vertexArray_);

	glGenBuffers(1, &c.vertexBuf_);
	glBindBuffer(GL_ARRAY_BUFFER, c.vertexBuf_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &c.uvBuf_);
	glBindBuffer(GL_ARRAY_BUFFER, c.uvBuf_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

	glGenBuffers(1, &c.normalBuf_);
	glBindBuffer(GL_ARRAY_BUFFER, c.normalBuf_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);

	glGenBuffers(1, &c.elementBuf_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, c.elementBuf_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	numIndices_ = sizeof(indices);
}

Cube::~Cube()
{
	puts("~Cube()");
	alive = false;
	glDeleteBuffers(1, &c.vertexBuf_);
	glDeleteBuffers(1, &c.uvBuf_);
	glDeleteBuffers(1, &c.normalBuf_);
	glDeleteBuffers(1, &c.elementBuf_);
	glDeleteVertexArrays(1, &c.vertexArray_);
}