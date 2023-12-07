#include "Input/V1KeyActionManager.h"

namespace Importal
{
  void V1KeyActionManager::ProcessActions()
  {
    for (auto& action : _actions)
      action.action((float)(KeyManager::GetKey(action.lKey).IsDown() - KeyManager::GetKey(action.rKey).IsDown()));
  }

  void Importal::V1KeyActionManager::BindAction(int lKey, int rKey, const std::function<void(float)>& action)
  {
    _actions.push_back({ action, lKey, rKey });
  }
}