#include "Camera.h"

glm::vec3 Importal::Camera::_pos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 Importal::Camera::_front = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 Importal::Camera::_up = glm::vec3(0.0f, 1.0f, 0.0f);
float Importal::Camera::_sensitivity = 0.1f;
float Importal::Camera::_speed = 3.0f;

void Importal::Camera::Rotate(const glm::vec3& rotation)
{
  static glm::vec3 direction;
  direction.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
  direction.y = sin(glm::radians(rotation.x));
  direction.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
  _front = glm::normalize(direction);
}

void Importal::Camera::MoveRelationly(const glm::vec3& movement, float deltaTime)
{
  auto rawMove = movement.y * _front + movement.x * glm::normalize(glm::cross(_front, _up));
  if (rawMove != glm::vec3(0.0f, 0.0f, 0.0f))
    rawMove = glm::normalize(rawMove);

  _pos += rawMove * _speed * deltaTime;
}

void Importal::Camera::OnMouseMove(float xPos, float yPos)
{
    static float xOff, yOff;
    static glm::vec3 rotation = glm::vec3(0.0f, 90.0f, 0.0f);
    static float xLast = xPos;
    static float yLast = yPos;

    xOff = xPos - xLast;
    yOff = yPos - yLast;
    xLast = xPos;
    yLast = yPos;

    xOff *= _sensitivity;
    yOff *= _sensitivity;

    rotation.x += yOff;
    rotation.y += xOff;

    rotation.x = glm::clamp(rotation.x, -89.9f, 89.9f);

    Rotate(rotation);
}

glm::mat4 Importal::Camera::GetView()
{
  return  glm::lookAt(_pos, glm::vec3(_pos - _front), _up);
}
