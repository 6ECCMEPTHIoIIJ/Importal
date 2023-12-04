#pragma once

#include <GL/glew.h>
#include <fstream>
#include <sstream>

namespace Importal
{
  class ShaderReader
  {
  public:
    static std::string ParseFile(std::string filename)
    {
      std::ifstream f;
      f.open(filename);
      if (!f.is_open())
        throw std::exception();
      std::stringstream ss;
      ss << f.rdbuf();
      return ss.str();
    }
  };
}