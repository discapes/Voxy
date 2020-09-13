#include "Shaders.h"
#include "Light.h"
#include "Model.h"

class MonoLightShaders : public Shaders
{
	const Camera& camera;
	const Light& light;

	const char* vertexShaderName;
	const char* fragmentShaderName;

	GLuint uniLightPos{};
	GLuint uniMVP{};
	GLuint uniM{};
	GLuint uniV{};
	GLuint uniTex{};
	GLuint uniLightColor{};

public:
	MonoLightShaders(const char* vertexShaderName, const char* fragmentShaderName, const Camera& camera, const Light& light);

	void draw(const Model& model, const mat4& modelMatrix);

	void draw(const Model& model, vec3 location)
	{
		return draw(model, glm::translate(mat4(1), location));
	}

	~MonoLightShaders();
};