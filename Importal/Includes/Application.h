#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Importal
{
  enum class WindowModes
  {
    Windowed,
    Fullscreen
  };

  struct WindowData
  {
    GLuint width;
    GLuint height;
    const GLchar* title;
    WindowModes mode;
  };

  class Application
  {
  public:
    Application();

    void Run();

  private:
    static void KeyCallback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods);

    GLFWwindow* _window;
  };
}