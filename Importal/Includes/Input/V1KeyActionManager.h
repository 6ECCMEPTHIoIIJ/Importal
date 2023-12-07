#pragma once

#include <array>
#include <vector>
#include <functional>

#include "KeyManager.h"
#include <stdexcept>
#include <format>

namespace Importal 
{
  class V1KeyActionManager
  {
    struct Action
    {
      std::function<void(float)> action;
      int lKey;
      int rKey;
    };

  public:
    V1KeyActionManager() = default;
    V1KeyActionManager(const V1KeyActionManager&) = delete;
    V1KeyActionManager(V1KeyActionManager&&) = delete;

    void ProcessActions();
    void BindAction(int lKey, int rKey, const std::function<void(float)>& action);

  private:
    std::vector<Action> _actions;
  };
}