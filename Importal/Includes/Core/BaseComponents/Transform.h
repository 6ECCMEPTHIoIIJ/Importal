#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core/GameComponent.h"

namespace Importal::Core {
  class Transform :
    public GameComponent
  {
    /* Transform(Transform* transfrom) {
     }*/



  private:
    glm::vec3
      _x = glm::vec3(0, 0, 0),
      _y = glm::vec3(0, 0, 0),
      _z = glm::vec3(0, 0, 0);
    double _xScale = 1, _yScale = 1, _zScale = 1;
  };
}



