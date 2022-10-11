#include "glew.h"
#include "glfw3.h"
#include "Object.h"
#include <iostream>

void render(GLFWwindow* window, RendererObject* object)
{
    object->bind();
    const static GLfloat red[] = {1.0f, 0.0f, 0.0f, 1.0f};
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, object->vertexPositionsSize);
    glfwSwapBuffers(window);
}