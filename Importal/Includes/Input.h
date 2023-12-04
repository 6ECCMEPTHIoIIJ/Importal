#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Importal
{
  class Input
  {
  public:
    static void SetKeyAction(GLint keyCode, GLint action);
    static GLint GetKeyAction(GLint keyCode);
  private:
    static GLint _keys[GLFW_KEY_LAST + 1];
  };
}