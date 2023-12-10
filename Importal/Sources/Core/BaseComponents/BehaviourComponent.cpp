#include "Core/BaseComponents/BehaviourComponent.h"

bool Importal::Core::BehaviourComponent::Enabled()
{
  return _enabled;
}

void Importal::Core::BehaviourComponent::Enable()
{
  _enabled = true;
}

void Importal::Core::BehaviourComponent::Disable()
{
  _enabled = false;
}

void Importal::Core::BehaviourComponent::Tick(double deltaTime)
{
  if (_enabled = false) {
    return;
  }
}
