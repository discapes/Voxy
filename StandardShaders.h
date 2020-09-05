#include "Shaders.h"
#include "Model.h"

class StandardShaders : public Shaders
{
	const char* vertexShaderName;
	const char* fragmentShaderName;

	GLuint program{};

	GLuint uniLightPos{};
	GLuint uniMVP{};
	GLuint uniM{};
	GLuint uniV{};
	GLuint uniTex{};
	GLuint uniLightColor{};

	glm::vec3 lightPos = glm::vec3(0, 4, 0);
	glm::vec3 lightColor = glm::vec3(20, 20, 20);

public:
	StandardShaders(const char* vertexShaderName, const char* fragmentShaderName)
		: vertexShaderName(vertexShaderName),
		fragmentShaderName(fragmentShaderName)
	{}

	void draw(Model& model, Camera* camera, mat4 modelMatrix);

	void draw(Model& model, Camera* camera, vec3 location)
	{
		return draw(model, camera, glm::translate(mat4(1), location));
	}

	void build();

	~StandardShaders();
};