#include "Timer.h"

namespace Importal
{
  void Timer::Update() {
    float currentTime = (float)glfwGetTime();
    _deltaTime = currentTime - _lastFrameTime;
    _lastFrameTime = currentTime;
  }

  float Timer::GetDeltaTime() const {
    return _deltaTime;
  }

  float Timer::GetLastFramTime() const {
    return _lastFrameTime;
  }
}