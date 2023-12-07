#pragma once

#include <GLFW/glfw3.h>
#include <array>

#include "Key.h"

namespace Importal
{
  class KeyManager
  {
  public:
    KeyManager() = delete;
    KeyManager(const KeyManager&) = delete;
    KeyManager(KeyManager&&) = delete;

    static const Key& GetKey(int key);
    static void PressKey(int key);
    static void ReleaseKey(int key);
    static void ProcessKeys();

  private:
    static std::array<Key, GLFW_KEY_LAST + 1> _keys;
  };
}