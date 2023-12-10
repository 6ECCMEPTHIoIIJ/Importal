#include "Core/GameObject.h"

Importal::Core::ComponentHasher Importal::Core::GameObject::_hasher;

Importal::Core::GameObject::~GameObject()
{
  for (auto& child : Children()) {
    delete child;
  }

  delete Transform();

  if (Parent() != nullptr) {
    Parent()->RemoveChildren(this);
  }

  for (auto& component : _behaviourComponents) {
    delete component.second;
  }
  // TODO: delete renderer
}

Importal::Core::GameObject* Importal::Core::GameObject::Parent()
{
  return _parent;
}

std::vector<Importal::Core::GameObject*> Importal::Core::GameObject::Children()
{
  return _children;
}

Importal::Core::Transform* Importal::Core::GameObject::Transform()
{
  return _transform;
}

void Importal::Core::GameObject::Tick(double deltaTime)
{
  // TODO: tick all child
  for (auto& gameObject : Children()) {
    gameObject->Tick(deltaTime);
  }

  //TODO: tick all components
  for (auto& behaviourComponent : _behaviourComponents) {
    behaviourComponent.second->Tick(deltaTime);
  }
}

void Importal::Core::GameObject::RemoveChildren(GameObject* children)
{
  int index = 0;
  for (auto& ptr : Children()) {
    if (ptr == children) {
      Children().erase(Children().begin() + index);
      return;
    }
    index++;
  }
}