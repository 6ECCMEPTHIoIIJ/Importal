#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <functional>
#include <unordered_map>
#include <array>

namespace Importal
{
  struct ActionState {
    bool Started = false;
    bool Performed = false;
    bool Canceled = false;
  };

  struct Key {
    ActionState State;
    bool Binded = false;
    std::function<void(ActionState)> Action;
  };

  class Input
  {
  public:
    Input() = default;
    Input(const Input&) = delete;
    Input(Input&&) = delete;

    void BindKeyAction(int keyCode, const std::function<void(ActionState)>& action) const;
    void UnbindKeyAction(int keyCode) const;
    void PressKey(int keyCode) const;
    void ReleaseKey(int keyCode) const;
    void ProcessKeyActions() const;

  private:
    void ProcessKeyAction(int keyCode) const;

    mutable std::array<Key, GLFW_KEY_LAST + 1> _keys;
  };
}