#pragma once

#include <Core/GameObject.h>

namespace Importal::Core {
  class GameComponent
  {
  public:
    GameComponent(GameObject* parent);
    

    ~GameComponent();

    Importal::Core::GameObject* GameObject();


#pragma region Removed ctors

    GameComponent(const GameComponent&) = delete;
    GameComponent(GameComponent&&) = delete;

#pragma endregion

  private:
    Importal::Core::GameObject* _gameObject = nullptr;

    //TODO : transform
  };
}

