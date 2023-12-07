#include "Input/KeyManager.h"

namespace Importal
{
  std::array<Key, GLFW_KEY_LAST + 1> KeyManager::_keys;

  const Key& KeyManager::GetKey(int key)
  {
    return _keys[key];
  }

  void KeyManager::PressKey(int key)
  {
    _keys[key].Press();
  }

  void KeyManager::ReleaseKey(int key)
  {
    _keys[key].Release();
  }

  void KeyManager::ProcessKeys()
  {
    for (auto& key : _keys)
      key.Process();
  }
}