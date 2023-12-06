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
#include "Timer.h"

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
    void CreateWindow();
    void DeleteWindow();
    GLboolean CheckWindowCreationStatus();
    void LogWindowCreationError();
    void RegisterWindow();
    void ProcessInputActions();

    static void HandleWindowResize(GLFWwindow* handler, GLint width, GLint height);
    static void HandleKeyInput(GLFWwindow* handler, int key, int scancode, int action, int mods);

    glm::vec3 _camMoveDir = glm::vec3(0.0f, 0.0f, 0.0f);
    bool moveF = false;
    bool moveB = false;
    bool moveR = false;
    bool moveL = false;
    glm::vec3 _camPos = glm::vec3(0.0f, 0.0f, 3.0f);
    Timer _time;
    Window* _window = nullptr;
    static std::unordered_map<const GLFWwindow*, Window*> _windows;
  };
}