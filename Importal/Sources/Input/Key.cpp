#include "Input/Key.h"

namespace Importal
{
  void Key::Press()
  {
    _cur = true;
  }

  void Key::Release()
  {
    _cur = false;
  }

  void Key::Process()
  {
    _prev = _cur;
  }

  bool Key::IsUp() const
  {
    return !_cur;
  }

  bool Key::IsDown() const
  {
    return _cur;
  }

  bool Key::IsJustPressed() const
  {
    return !_prev && _cur;
  }

  bool Key::IsJustReleased() const
  {
    return _prev && !_cur;
  }
}