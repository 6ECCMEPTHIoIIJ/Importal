#include "Input/V2ActionManager.h"

#include <stdexcept>
#include <format>

namespace Importal
{
  void V2KeyActionManager::ProcessActions() 
  {
    for (auto& action : _actions)
      action.action((float)(KeyManager::GetKey(action.lKey).IsDown() - KeyManager::GetKey(action.rKey).IsDown()),
        (float)(KeyManager::GetKey(action.fKey).IsDown() - KeyManager::GetKey(action.bKey).IsDown()));
  }

  void V2KeyActionManager::BindAction(int fKey, int lKey, int bKey, int rKey, const std::function<void(float, float)>& action)
  {
    _actions.push_back({ action, fKey, lKey, bKey, rKey });
  }
}
