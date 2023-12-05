#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <unordered_map>

#include "Window.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ArrayBuffer.h"
#include "Shader.h"

namespace Importal
{
  class Application
  {
  public:
    Application();
    Application(const Application&) = delete;
    Application(Application&&) = delete;
    void Run();
    ~Application();

  private:
    glm::vec3 _camPos = glm::vec3(0.0f, 0.0f, 0.0f);
    void CreateWindow();
    void DeleteWindow();
    GLboolean CheckWindowCreationStatus();
    void LogWindowCreationError();
    void RegisterWindow();
    static void HandleWindowResize(GLFWwindow* handler, GLint width, GLint height);
    static void HandleKeyInput(GLFWwindow* handler, int key, int scancode, int action, int mods);

    Window* _window = nullptr;
    static std::unordered_map<const GLFWwindow*, Window*> _windows;
  };
}