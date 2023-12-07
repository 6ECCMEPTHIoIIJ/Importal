#pragma once

#include <array>
#include <vector>
#include <functional>

#include "KeyManager.h"

namespace Importal
{
  class V2KeyActionManager
  {
    struct Action
    {
      std::function<void(int, int)> action;
      int fKey;
      int lKey;
      int bKey;
      int rKey;
    };

  public:
    V2KeyActionManager() = default;
    V2KeyActionManager(const V2KeyActionManager&) = delete;
    V2KeyActionManager(V2KeyActionManager&&) = delete;

    void ProcessActions();
    void BindAction(int fKey, int lKey, int bKey, int rKey, const std::function<void(float, float)>& action);

  private:
    std::vector<Action> _actions;
  };
}