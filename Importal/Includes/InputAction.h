#pragma once

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

namespace Importal
{
  struct InputAction
  {
    virtual ~InputAction() = default;
  };

  class InputVector2 : public InputAction
  {
  public:
    void BindKeys(int fKeyCode, int lKeyCode, int bKeyCode, int rKeyCode)
    {

    }

    glm::vec2 ReadInput() {
      return
    }

  private:
    glm::vec2 _rawInput;
  };

  struct InputButton : public InputAction
  {

  };
}