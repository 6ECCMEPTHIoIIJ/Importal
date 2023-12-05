#include "Window.h"


namespace Importal
{
  void Window::Create(int width, int height, const std::string& title)
  {
    _width = width;
    _height = height;
    _handler = glfwCreateWindow(width, width, title.c_str(), glfwGetPrimaryMonitor(), nullptr);
  }

  void Window::OnResize(int width, int height)
  {
    glViewport(0, 0, width, height);
    _width = width;
    _height = height;
  }

  const Input* Window::GetInput() const
  {
    return &_input;
  }

  int Window::GetWidth() const
  {
    return _width;
  }

  int Window::GetHeight() const
  {
    return _height;
  }

  GLFWwindow* Window::GetHandler()
  {
    return _handler;
  }

  Window::~Window()
  {
    if (_handler != nullptr);
    glfwDestroyWindow(_handler);
  }
}