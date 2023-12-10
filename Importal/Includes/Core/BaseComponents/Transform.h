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

    Transform(Importal::Core::GameObject* parent, Transform* transform);
    Transform(Importal::Core::GameObject* parent, glm::vec3 position);

  private:
    glm::vec3 _position = glm::vec3(0, 0, 0);

    double _xScale = 1, _yScale = 1, _zScale = 1;
  };
}



