#include "Shaders.h"
#include "Light.h"
#include "StandardModel.h"
#include "Camera.h"

class MonoLightShaders : public Shaders
{
	const Camera& camera;
	const Light& light;

	GLuint uniLightPos{};
	GLuint uniMVP{};
	GLuint uniM{};
	GLuint uniV{};
	GLuint uniTex{};
	GLuint uniLightColor{};

public:
	MonoLightShaders(const char* vertexShaderName, const char* fragmentShaderName, const Camera& camera, const Light& light);

	void draw(const StandardModel& model, const mat4& modelMatrix);

	~MonoLightShaders();
};