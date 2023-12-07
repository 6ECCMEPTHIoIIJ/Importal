#pragma once

#include <array>

#include "KeyManager.h"
#include "V2ActionManager.h"
#include "V1ActionManager.h"
#include "TriggerActionManager.h"

namespace Importal 
{
  class InputManager
  {
  public:
    InputManager() = delete;
    InputManager(const InputManager&) = delete;
    InputManager(InputManager&&) = delete;

    static void BindAction(int fKey, int lKey, int bKey, int rKey, const std::function<void(float, float)>& action);
    static void BindAction(int lKey, int rKey, const std::function<void(float)>& action);
    static void BindAction(int key, const std::function<void(const Key&)>& action);
    static void ProcessActions();

  private:
    static V2KeyActionManager _v2KeyManager;
    static V1KeyActionManager _v1KeyManager;
    static TrigerKeyActionManager _triggerKeyManager;
  };
}