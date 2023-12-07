#include "Input/TriggerKeyActionManager.h"

#include <stdexcept>
#include <format>

namespace Importal
{
  void TrigerKeyActionManager::ProcessActions()
  {
    for (auto& action : _actions)
      action.action(KeyManager::GetKey(action.key));
  }

  void TrigerKeyActionManager::BindAction(int key, const std::function<void(const Key&)>& action)
  {
    _actions.push_back({ action, key });
  }
}