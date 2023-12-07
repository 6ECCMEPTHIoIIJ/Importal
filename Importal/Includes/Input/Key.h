#pragma once

namespace Importal
{
  class Key
  {
  public:
    void Press();
    void Release();
    void Process();
    bool IsUp() const;
    bool IsDown() const;
    bool IsJustPressed() const;
    bool IsJustReleased() const;

  private:
    bool _prev = false;
    bool _cur = false;
  };
}