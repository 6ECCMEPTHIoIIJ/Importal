#include "Core/GameComponent.h"

Importal::Core::GameComponent::GameComponent(Importal::Core::GameObject* gameObject) 
{
  _gameObject = gameObject;
}


Importal::Core::GameObject* Importal::Core::GameComponent::GameObject()
{
    return _gameObject;
}
