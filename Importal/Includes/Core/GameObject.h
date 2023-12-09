#pragma once

#include <vector>

class GameComponent;
#include "GameComponent.h"
#include "ComponentHasher.h"
#include "Location.h"


namespace Importal::Core {
  class GameObject
  {
  public:
#pragma region Ctors

    GameObject(Location* location);
    GameObject(Location* location, GameObject* parent);
    ~GameObject();

#pragma endregion

    void Deatach(GameObject* child);

    GameObject* Parent();
    std::vector<GameObject*> Children();

    bool AddComponent(GameComponent* component);

    template<class T, class ...Args>
      requires std::is_base_of_v<GameComponent, T>
    T* AddComponent(Args... args) {
      static_assert(std::is_base_of<GameComponent, T>);
    }

#pragma region Removed ctors

    GameObject(const GameObject&) = delete;
    GameObject(GameObject&&) = delete;

#pragma endregion

  private:
    GameObject* _parent = nullptr;
    std::vector<GameObject*> _children = std::vector<GameObject*>();
    static ComponentHasher _hasher;

  };
}

