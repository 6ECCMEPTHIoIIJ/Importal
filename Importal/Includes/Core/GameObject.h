#pragma once

#include <vector>

class GameComponent;
#include "GameComponent.h"


namespace Importal::Core {
  class GameObject
  {
  public:
#pragma region Ctors

    GameObject();
    GameObject(GameObject* parent);
    ~GameObject();

#pragma endregion


    void Deatach(GameObject* child);


    GameObject* Parent();
    std::vector<GameObject*> Children();

#pragma region Removed ctors

    GameObject(const GameObject&) = delete;
    GameObject(GameObject&&) = delete;

#pragma endregion

  private:
    GameObject* _parent = nullptr;
    std::vector<GameObject*> _children = std::vector<GameObject*>();
  };
}

