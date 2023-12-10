#include <stdexcept>

#include "Core/BaseComponents/Transform.h"

Importal::Core::Transform::Transform(Importal::Core::GameObject* gameObject, Transform* transform)
  : GameComponent(gameObject)
{
  if (transform == nullptr) {
    throw std::invalid_argument("Transfrom nullptr");
  }

  this->_position = transform->_position;
  this->_scale = transform->_scale;
  this->_rotation = transform->_rotation;
}

Importal::Core::Transform::Transform(Importal::Core::GameObject* gameObject, glm::vec3 position)
  : GameComponent(gameObject)
{
  this->_position = position;
}

Importal::Core::Transform::Transform(Importal::Core::GameObject* gameObject, glm::vec3 position, glm::vec3 scale)
  :Transform(gameObject, position)
{
  this->_scale = scale;
}

Importal::Core::Transform::Transform(Importal::Core::GameObject* gameObject, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
  :Transform(gameObject, position, scale)
{
  this->_rotation = rotation;
}

glm::vec3 Importal::Core::Transform::Position()
{
  return _position;
}

glm::vec3 Importal::Core::Transform::Scale()
{
  return _scale;
}

glm::vec3 Importal::Core::Transform::Rotation()
{
  return _rotation;
}

void Importal::Core::Transform::Move(glm::vec3 vector)
{
  _position += vector;
}



