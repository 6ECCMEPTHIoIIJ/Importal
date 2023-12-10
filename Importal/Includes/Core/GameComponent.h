#pragma once

#include "All.h"

//#include "Core/GameObject.h"

namespace Importal::Core {
  class GameComponent
  {
  public:
    GameComponent(GameObject* gameObject);

    virtual ~GameComponent() = default;

    GameObject* GameObject();

#pragma region Removed ctors

    GameComponent(const GameComponent&) = delete;
    GameComponent(GameComponent&&) = delete;

#pragma endregion

  private:
    Importal::Core::GameObject* _gameObject = nullptr;

  };
}

