#include <stdexcept>

#include "Core/GameComponent.h"

Importal::Core::GameComponent::GameComponent(Importal::Core::GameObject* gameObject) 
{
  if (gameObject == nullptr) {
    throw std::invalid_argument("Game object nullptr");
  }

  _gameObject = gameObject;
}

Importal::Core::GameObject* Importal::Core::GameComponent::GameObject()
{
    return _gameObject;
}
