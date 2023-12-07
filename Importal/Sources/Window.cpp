#include "Window.h"


namespace Importal
{
  GLFWwindow* Window::Create(int w, int h, const std::string& title)
  {
    _w = w;
    _h = h;
    _hWnd = glfwCreateWindow(w, w, title.c_str(), nullptr, nullptr);

    return _hWnd;
  }

  void Window::OnResize(int w, int h)
  {
    glViewport(0, 0, w, h);
    _w = w;
    _h = h;
  }

  int Window::GetW() const
  {
    return _w;
  }

  int Window::GetH() const
  {
    return _h;
  }

  GLFWwindow* Window::GetHWnd()
  {
    return _hWnd;
  }

  Window::~Window()
  {
    if (_hWnd != nullptr)
      glfwDestroyWindow(_hWnd);
  }
}