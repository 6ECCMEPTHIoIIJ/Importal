#pragma once

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

namespace Importal
{
  extern bool stopped;
  extern bool move;

  class Camera
  {
  public:
    Camera() = delete;
    Camera(const Camera&) = delete;
    Camera(Camera&&) = delete;

    static void Rotate(const glm::vec3& rotation);
    static void MoveRelationly(const glm::vec3& movement, float deltaTime);
    static void OnMouseMove(float xPos, float yPos);
    static glm::mat4 GetView();
    static glm::vec3 GetPos();
    static glm::vec3 GetRotation();
    static glm::vec3 GetFront() {
      return _front;
    }
    static void TranslateRelationly(const glm::vec3& translate, float scale);
    static void SetPos(const glm::vec3& pos);

  private:
    static glm::vec3 _pos;
    static glm::vec3 _front;
    static glm::vec3 _up;
    static float _sensitivity;
    static float _speed;
    static glm::vec3 _rotation;
  };
}