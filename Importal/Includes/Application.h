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
    static void HandleWindowResize(GLFWwindow* handler, GLint width, GLint height);
    static void HandleKeyInput(GLFWwindow* handler, int key, int scancode, int action, int mods);
    static void HandleMouseInput(GLFWwindow* window, double xpos, double ypos);

    static Timer _time;
    static Window _window;
  };
}