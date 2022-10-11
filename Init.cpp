#include "Input.h"
#include "Camera.h"
#include "glew.h"
#include "glfw3.h"

void initKeyboardAndMouseInput(GLFWwindow* window, Camera* camera)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 0.0, 0.0, 1.0);
	int width, height;
	glActiveTexture(GL_TEXTURE0);
	glfwGetWindowSize(window, &width, &height);
	glfwSetCursorPos(window, width / 2.0, height / 2.0);
	glfwSetWindowUserPointer(window, static_cast<void*>(camera));
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPosCallback(window, cursorPosCallback);
}