#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

namespace Importal
{
  class Window
  {
  public:
    Window() = default;
    Window(const Window&) = delete;
    Window(Window&&) = delete;
    GLFWwindow* Create(int w, int h, const std::string& title);
    void OnResize(int w, int h);
    int GetW() const;
    int GetH() const;
    GLFWwindow* GetHWnd();
    ~Window();

  private:
    int _w = 0;
    int _h = 0;
    GLFWwindow* _hWnd = nullptr;
  };
}