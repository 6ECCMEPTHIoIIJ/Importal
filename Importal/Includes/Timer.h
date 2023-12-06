#pragma once

#include <GLFW/glfw3.h>

namespace Importal 
{
  class Timer 
  {
  public:
    Timer() = default;
    Timer(const Timer&) = delete;
    Timer(Timer&&) = delete;
    void Update();
    float GetDeltaTime() const;
    float GetLastFramTime() const;

  private:
    float _lastFrameTime = 0;
    float _deltaTime = 0;
  };
}