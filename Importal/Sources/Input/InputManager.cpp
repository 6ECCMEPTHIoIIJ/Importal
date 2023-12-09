#include "Input/InputManager.h"

namespace Importal {
  V2KeyActionManager InputManager::_v2KeyManager;
  V1KeyActionManager InputManager::_v1KeyManager;
  TrigerKeyActionManager InputManager::_triggerKeyManager;

  void InputManager::BindAction(int fKey, int lKey, int bKey, int rKey, const std::function<void(float, float)>& action)
  {
    _v2KeyManager.BindAction(fKey, lKey, bKey, rKey, action);
  }

  void InputManager::BindAction(int lKey, int rKey, const std::function<void(float)>& action)
  {
    _v1KeyManager.BindAction(lKey, rKey, action);
  }

  void InputManager::BindAction(int key, const std::function<void(const Key&)>& action)
  {
    _triggerKeyManager.BindAction(key, action);
  }

  void InputManager::ProcessActions()
  {
    _v2KeyManager.ProcessActions();
    _v1KeyManager.ProcessActions();
    _triggerKeyManager.ProcessActions();
    KeyManager::ProcessKeys();
  }
}

