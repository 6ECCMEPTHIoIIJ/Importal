#pragma once

#include "../All.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../GameComponent.h"

namespace Importal::Core {
  class Transform : public GameComponent
  {
  public:

    Transform(Importal::Core::GameObject* gameObject, Transform* transform);
    Transform(Importal::Core::GameObject* gameObject, glm::vec3 position);
    Transform(Importal::Core::GameObject* gameObject, glm::vec3 position, glm::vec3 scale);
    Transform(Importal::Core::GameObject* gameObject, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);

    glm::vec3 Position();
    glm::vec3 Scale();
    glm::vec3 Rotation();

    void Move(glm::vec3 vector);

  private:
    glm::vec3 _position = glm::vec3(0, 0, 0);
    glm::vec3 _scale = glm::vec3(1);
    glm::vec3 _rotation = glm::vec3(0);
  };
}



