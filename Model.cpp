#include "Model.h"
#include "util/vboindexer.hpp"

Model::Model(const char* objName, const char* textureDDS)
{
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	texture = loadDDS(textureDDS);

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	loadOBJ(objName, vertices, uvs, normals);

	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;
	indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);

	glGenBuffers(1, &vertexBuf);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuf);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvBuf);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuf);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalBuf);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuf);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &elementBuf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

	numIndices = (GLsizei)indices.size();
}

Model::~Model()
{
	puts("~Model()");
	glDeleteBuffers(1, &vertexBuf);
	glDeleteBuffers(1, &uvBuf);
	glDeleteBuffers(1, &normalBuf);
	glDeleteBuffers(1, &elementBuf);
	glDeleteTextures(1, &texture);
	glDeleteVertexArrays(1, &vertexArray);
}