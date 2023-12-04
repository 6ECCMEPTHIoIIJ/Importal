#include "Input.h"

namespace Importal
{
  GLint Input::_keys[GLFW_KEY_LAST + 1] = {};

  void Input::SetKeyAction(GLint keyCode, GLint action)
  {
    if (keyCode == GLFW_KEY_UNKNOWN)
      return;

    _keys[keyCode] = action;
  }

  GLint Input::GetKeyAction(GLint keyCode)
  {
    return _keys[keyCode];
  }
}