#include "Shaders.h"
#include "Model.h"

class StandardShaders : public Shaders
{
	const Camera& camera;

	const char* vertexShaderName;
	const char* fragmentShaderName;

	GLuint uniLightPos{};
	GLuint uniMVP{};
	GLuint uniM{};
	GLuint uniV{};
	GLuint uniTex{};
	GLuint uniLightColor{};

	vec3 lightPos = vec3(0, 4, 0);
	vec3 lightColor = vec3(20, 20, 20);

public:
	StandardShaders(const char* vertexShaderName, const char* fragmentShaderName, const Camera& camera);

	void draw(const Model& model, const mat4& modelMatrix);

	void draw(const Model& model, vec3 location)
	{
		return draw(model, glm::translate(mat4(1), location));
	}

	void drawCube(const mat4& modelMatrix);

	void drawCube(vec3 location)
	{
		return drawCube(glm::translate(mat4(1), location));
	}

	~StandardShaders();
};