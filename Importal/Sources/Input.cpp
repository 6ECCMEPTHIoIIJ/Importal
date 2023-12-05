#include "Input.h"

namespace Importal
{
  void Input::BindAction(KeyState keyState, const std::function<void()>& action) const
  {
    _bindedActions[keyState] = action;
  }

  void Input::BindAction(int keyCode, int keyState, const std::function<void()>& action) const
  {
    BindAction({ keyCode, keyState }, action);
  }

  void Input::BindActionOnPress(int keyCode, const std::function<void()>& action) const
  {
    BindAction(keyCode, GLFW_PRESS, action);
  }

  void Input::UnbindAction(KeyState keyState) const
  {
    _bindedActions.erase(keyState);
  }

  void Input::UnbindAction(int keyCode, int keyState) const
  {
    UnbindAction({ keyCode, keyState });
  }

  void Input::UnbindActionOnPress(int keyCode) const
  {
    UnbindAction(keyCode, GLFW_PRESS);
  }

  void Input::UnbindActionOnRelease(int keyCode) const
  {
    UnbindAction(keyCode, GLFW_RELEASE);
  }

  void Input::UnbindActionOnRepeate(int keyCode) const
  {
    UnbindAction(keyCode, GLFW_REPEAT);
  }

  void Input::OnKeyInState(KeyState keyState) const
  {
    if (_bindedActions.contains(keyState))
      _bindedActions[keyState]();
  }

  void Input::OnKeyInState(int keyCode, int keyState) const
  {
    OnKeyInState({ keyCode, keyState });
  }

  void Input::OnKeyPressed(int keyCode) const
  {
    OnKeyInState(keyCode, GLFW_PRESS);
  }

  void Input::OnKeyReleased(int keyCode) const
  {
    OnKeyInState(keyCode, GLFW_RELEASE);
  }

  void Input::BindActionOnRelease(int keyCode, const std::function<void()>& action) const
  {
    BindAction(keyCode, GLFW_RELEASE, action);
  }

  void Input::BindActionOnRepeate(int keyCode, const std::function<void()>& action) const
  {
    BindAction(keyCode, GLFW_REPEAT, action);
  }
}