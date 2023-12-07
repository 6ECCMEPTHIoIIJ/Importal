#pragma once

#include <array>
#include <vector>
#include <functional>

#include "KeyManager.h"

namespace Importal
{
  class TrigerKeyActionManager
  {
    struct Action
    {
      std::function<void(const Key&)> action;
      int key;
    };

  public:
    TrigerKeyActionManager() = default;
    TrigerKeyActionManager(const TrigerKeyActionManager&) = delete;
    TrigerKeyActionManager(TrigerKeyActionManager&&) = delete;

    void ProcessActions();
    void BindAction(int key, const std::function<void(const Key&)>& action);

  private:
    std::vector<Action> _actions;
  };
}