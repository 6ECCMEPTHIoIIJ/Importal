#include "Input.h"

namespace Importal
{
  void Input::BindKeyAction(int keyCode, const std::function<void(ActionState)>& action) const
  {
    _keys[keyCode].Binded = true;
    _keys[keyCode].Action = action;
  }

  void Input::UnbindKeyAction(int keyCode) const
  {
    _keys[keyCode].Binded = false;
  }

  void Input::PressKey(int keyCode) const
  {
    _keys[keyCode].State.Started = true;
    _keys[keyCode].State.Performed = true;
    _keys[keyCode].State.Canceled = false;
  }

  void Input::ReleaseKey(int keyCode) const
  {
    _keys[keyCode].State.Started = false;
    _keys[keyCode].State.Performed = false;
    _keys[keyCode].State.Canceled = true;
  }

  void Input::ProcessKeyActions() const {
    for (int i = 0; i < _keys.size(); ++i)
      ProcessKeyAction(i);
  }

  void Input::ProcessKeyAction(int keyCode) const
  {
    if (_keys[keyCode].Binded)
      _keys[keyCode].Action(_keys[keyCode].State);

    _keys[keyCode].State.Started = false;
    _keys[keyCode].State.Canceled = false;
  }
}