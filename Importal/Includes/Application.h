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

    glm::vec3 _camPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 _camFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 _camUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 _direction;
    static double _lastX;
    static double _lastY;
    static float _offsetX;
    static float _offsetY;
    static float _yaw;
    static float _pitch;

    static Timer _time;
    static Window _window;
  };
}