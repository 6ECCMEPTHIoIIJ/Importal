#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>


#include "Input.h"

namespace Importal
{
  class Window
  {
  public:
    Window() = default;
    Window(const Window&) = delete;
    Window(Window&&) = delete;
    void Create(int width, int height, const std::string& title);
    void OnResize(int width, int height);
    const Input* GetInput() const;
    int GetWidth() const;
    int GetHeight() const;
    GLFWwindow* GetHandler();
    ~Window();

  private:
    int _width = 0;
    int _height = 0;
    Input _input;
    GLFWwindow* _handler = nullptr;
  };
}