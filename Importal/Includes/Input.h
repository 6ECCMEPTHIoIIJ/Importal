#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <functional>
#include <unordered_map>

namespace Importal
{
  class Input
  {
    struct KeyState
    {
      int Code;
      int State;

      bool operator==(const KeyState& lhs) const
      {
        return Code == lhs.Code && State == lhs.State;
      }

      struct Hash
      {
        size_t operator()(const KeyState& keyState) const
        {
          return (keyState.Code ^ ((size_t)(keyState.State) << 1) >> 1);
        }
      };
    };

  public:
    Input() = default;
    Input(const Input&) = delete;
    Input(Input&&) = delete;
    void BindAction(KeyState keyState, const std::function<void()>& action) const;
    void BindAction(int keyCode, int keyState, const std::function<void()>& action) const;
    void BindActionOnPress(int keyCode, const std::function<void()>& action) const;
    void BindActionOnRelease(int keyCode, const std::function<void()>& action) const;
    void BindActionOnRepeate(int keyCode, const std::function<void()>& action) const;
    void UnbindAction(KeyState keyState) const;
    void UnbindAction(int keyCode, int keyState) const;
    void UnbindActionOnPress(int keyCode) const;
    void UnbindActionOnRelease(int keyCode) const;
    void UnbindActionOnRepeate(int keyCode) const;
    void OnKeyInState(KeyState keyState) const;
    void OnKeyInState(int keyCode, int keyState) const;
    void OnKeyPressed(int keyCode) const;
    void OnKeyReleased(int keyCode)  const;

  private:
    mutable std::unordered_map<KeyState, std::function<void()>, KeyState::Hash> _bindedActions;
  };
}