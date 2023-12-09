#pragma once

class GameComponent;
#include "Core/GameComponent.h"

namespace Importal::Core {
  class BehaviourComponent : GameComponent
  {
  public:
    bool Enabled();

    void Enable();
    void Disable();

#pragma region Callbacks

    void Tick(double deltaTime);

#pragma endregion
  };
}