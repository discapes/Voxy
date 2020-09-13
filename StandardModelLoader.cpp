#include "StandardModel.h"
#include "StandardModelLoader.h"
#include "util/vboindexer.hpp"
#include "util/texture.hpp"
#include "util/objloader.hpp"
#include "Cube.h"

StandardModel StandardModelLoader::loadObjAndDDS(const char* objName, const char* textureDDS)
{
	StandardModel m;

	glGenVertexArrays(1, &m.vertexArray);
	glBindVertexArray(m.vertexArray);

	m.texture = loadDDS(textureDDS);

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	loadOBJ(objName, vertices, uvs, normals);

	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;
	indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);

	glGenBuffers(1, &m.vertexBuf);
	glBindBuffer(GL_ARRAY_BUFFER, m.vertexBuf);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m.uvBuf);
	glBindBuffer(GL_ARRAY_BUFFER, m.uvBuf);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m.normalBuf);
	glBindBuffer(GL_ARRAY_BUFFER, m.normalBuf);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m.elementBuf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.elementBuf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

	m.numIndices = (GLsizei)indices.size();
	return m;
}

StandardModel StandardModelLoader::loadCubeAndDDS(const char* textureDDS)
{
	StandardModel m;

	glGenVertexArrays(1, &m.vertexArray);
	glBindVertexArray(m.vertexArray);

	m.texture = loadDDS(textureDDS);

	glGenBuffers(1, &m.vertexBuf);
	glBindBuffer(GL_ARRAY_BUFFER, m.vertexBuf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::vertices), Cube::vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &m.uvBuf);
	glBindBuffer(GL_ARRAY_BUFFER, m.uvBuf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::uvs), Cube::uvs, GL_STATIC_DRAW);

	glGenBuffers(1, &m.normalBuf);
	glBindBuffer(GL_ARRAY_BUFFER, m.normalBuf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::normals), Cube::normals, GL_STATIC_DRAW);

	glGenBuffers(1, &m.elementBuf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.elementBuf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Cube::indices), Cube::indices, GL_STATIC_DRAW);

	m.numIndices = sizeof(Cube::indices);
	return m;
}