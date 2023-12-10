#include <stdexcept>

#include "Core/BaseComponents/Transform.h"

Importal::Core::Transform::Transform(Importal::Core::GameObject* gameObject, Transform* transform)
  : GameComponent(gameObject)
{
  if (transform == nullptr) {
    throw std::invalid_argument("Transfrom nullptr");
  }

  this->_localPosition = transform->_localPosition;
  this->_scale = transform->_scale;
  this->_rotation = transform->_rotation;
}

Importal::Core::Transform::Transform(Importal::Core::GameObject* gameObject, glm::vec3 position)
  : GameComponent(gameObject)
{
  this->_localPosition = position;
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
  return _localPosition;
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
  _localPosition += vector;
}

glm::vec3 Importal::Core::Transform::LocalPosition()
{
  return _localPosition;
}

glm::vec3 Importal::Core::Transform::GlobalPosition()
{
  Importal::Core::GameObject* parent = GameObject()->Parent();

  glm::vec3 globalPos = LocalPosition();
  while (parent != nullptr) {
    globalPos += parent->Transform()->LocalPosition();
    parent = parent->Parent();
  }

  return globalPos;
}