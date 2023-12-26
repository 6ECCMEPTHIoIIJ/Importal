#include "Camera.h"

namespace Importal {
  bool stopped = false;
  bool move = false;
}



glm::vec3 Importal::Camera::_pos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 Importal::Camera::_front = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 Importal::Camera::_up = glm::vec3(0.0f, 1.0f, 0.0f);
float Importal::Camera::_sensitivity = 0.1f;
float Importal::Camera::_speed = 7.0f;
glm::vec3 Importal::Camera::_rotation = glm::vec3(0.0f, 90.0f, 0.0f);

void Importal::Camera::Rotate(const glm::vec3& rotation)
{
  static glm::vec3 direction;
  direction.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
  direction.y = sin(glm::radians(rotation.x));
  direction.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
  _front = glm::normalize(direction);
  _rotation = rotation;
}

void Importal::Camera::MoveRelationly(const glm::vec3& movement, float deltaTime)
{
  auto rawMove = movement.y * _front + movement.x * glm::normalize(glm::cross(_front, _up));
  if (rawMove != glm::vec3(0.0f, 0.0f, 0.0f))
    rawMove = glm::normalize(rawMove);

  _pos += rawMove * _speed * deltaTime;
}

void Importal::Camera::TranslateRelationly(const glm::vec3& translate, float scale)
{
  auto rawMove = translate.y * _front + translate.x * glm::normalize(glm::cross(_front, _up));
  if (rawMove != glm::vec3(0.0f, 0.0f, 0.0f))
    rawMove = glm::normalize(rawMove);
  _pos += rawMove * scale;
}


void Importal::Camera::OnMouseMove(float xPos, float yPos)
{
    static float xOff, yOff;
    static float xLast = xPos;
    static float yLast = yPos;

    xOff = xPos - xLast;
    yOff = yPos - yLast;
    xLast = xPos;
    yLast = yPos;

    xOff *= _sensitivity;
    yOff *= _sensitivity;

    _rotation.x += yOff;
    _rotation.y += xOff;

    _rotation.x = glm::clamp(_rotation.x, stopped ? -89.0f : 10.0f, stopped ? 89.0f : 60.0f);

    Rotate(_rotation);
}

glm::mat4 Importal::Camera::GetView()
{
  return  glm::lookAt(_pos, glm::vec3(_pos - _front), _up);
}

glm::vec3 Importal::Camera::GetPos() {
  return _pos;
}

glm::vec3 Importal::Camera::GetRotation() {
  return _rotation;
}

void Importal::Camera::SetPos(const glm::vec3& pos) {
  _pos = pos;
}
