#pragma once

#include "../All.h"

#include "Core/GameComponent.h"

namespace Importal::Core {
  class BehaviourComponent : GameComponent
  {
  public:
    bool Enabled();

    void Enable();
    void Disable();

    virtual ~BehaviourComponent();

#pragma region Callbacks

    virtual void Tick(double deltaTime);

#pragma endregion

  private:
    bool _enabled = true;
  };
}