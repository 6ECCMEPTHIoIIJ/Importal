#pragma once

#include <Core/GameObject.h>

namespace Importal::Core {
  class GameComponent
  {
  public:
    Importal::Core::GameObject* GameObject();

  private:
    Importal::Core::GameObject* _gameObject = nullptr;

    //TODO : transform
  };
}

