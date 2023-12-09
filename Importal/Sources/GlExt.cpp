#include "GlExt.h"

namespace Importal 
{
  void GlClearErrors()
  {
    while (glGetError() != GL_NO_ERROR);
  }

  bool GlCheckErrors(const char* func, const char* file, int line)
  {
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
      std::cout << std::format("| [OpenGL Error] ({})\n| Func: {}\n| File: {}\n| Line: {} ", error, func, file, line) << std::endl;
      return false;
    }

    return true;
  }
}
