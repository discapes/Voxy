#ifndef CONTROLS_HPP
#define CONTROLS_HPP

void setWindow(GLFWwindow* _window);
void computeMatricesFromInputs();
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
extern glm::vec3 position;

#endif