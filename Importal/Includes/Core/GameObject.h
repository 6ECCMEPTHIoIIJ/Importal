#pragma once

#include "All.h"

#include <vector>
#include <unordered_map>

#include "ComponentHasher.h"
#include "Location.h"
#include "BaseComponents/Transform.h"

namespace Importal::Core {
  class GameObject final
  {
  public:
#pragma region Ctors

    GameObject(Location* location);
    GameObject(Location* location, Importal::Core::GameObject* parent);

    ~GameObject();

#pragma endregion

    /*void Deatach(GameObject* child);*/

    GameObject* Parent();
    std::vector<GameObject*> Children();
    Importal::Core::Transform* Transform();

    bool AddComponent(GameComponent* component);

    template<class T, class ...Args>
      requires std::is_base_of_v<GameComponent, T>
    T* AddComponent(Args... args);

    template<class T, class ...Args>
      requires std::is_base_of_v<GameComponent, T>
    T* GetCompoent();

#pragma region Removed ctors

    GameObject(const GameObject&) = delete;
    GameObject(GameObject&&) = delete;

#pragma endregion

  private:
    GameObject* _parent = nullptr;
    Importal::Core::Transform* _transform;
    std::vector<GameObject*> _children = std::vector<GameObject*>();

    std::unordered_map<ComponentHasher::Hash, BehaviourComponent*> _behaviourComponents;
    std::unordered_map<ComponentHasher::Hash, GameComponent*> _components;

    static ComponentHasher _hasher;
  };
}

