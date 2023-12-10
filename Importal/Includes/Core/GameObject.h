#pragma once

#include "All.h"

#include <vector>
#include <unordered_map>

#include "ComponentHasher.h"
#include "Location.h"
#include "GameComponent.h"
#include "BaseComponents/BehaviourComponent.h"
#include "BaseComponents/Transform.h"

namespace Importal::Core {
  class GameObject final
  {
  public:
#pragma region Ctors

    GameObject();
    GameObject(GameObject* parent);
    GameObject(GameObject* parent, Transform localPosition);

    ~GameObject();

#pragma endregion

    /*void Deatach(GameObject* child);*/

    GameObject* Parent();
    std::vector<GameObject*> Children();
    Importal::Core::Transform* Transform();

    void Tick(double deltaTime);

    template<class T, class ...Args>
      requires std::is_base_of_v<BehaviourComponent, T>
    bool AddComponent(T* component) {
      if (_behaviourComponents.contains(_hasher.operator() < T > ())) {
        return false;
      }

      _behaviourComponents[_hasher.operator() < T > ()] = component;

      return true;
    }

    template<class T, class ...Args>
      requires std::is_base_of_v<BehaviourComponent, T>
    T* AddComponent(Args... args) {
      if (_behaviourComponents.contains(_hasher.operator() < T > ())) {
        return nullptr;
      }

      T* component = new T(args...);
      _behaviourComponents[_hasher.operator() < T > ()] = component;

      return component;
    }

    template<class T, class ...Args>
      requires std::is_base_of_v<BehaviourComponent, T>
    T* GetCompoent() {
      if (_behaviourComponents.contains(_hasher.operator() < T > ())) {
        return nullptr;
      }

      return dynamic_cast<T*>(_behaviourComponents[_hasher.operator() < T > ()]);
    }

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

    void RemoveChildren(GameObject* children);
  };
}

