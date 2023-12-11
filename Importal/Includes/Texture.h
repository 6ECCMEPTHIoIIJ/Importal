#pragma once
#include "GlExt.h"

namespace Importal
{
  class Texture
  {
  public:
    Texture(const std::string& path,
            GLint MIN_FILTER = GL_LINEAR,
            GLint MAG_FILTER = GL_LINEAR,
            GLint WRAP_S = GL_CLAMP_TO_EDGE,
            GLint WRAP_T = GL_CLAMP_TO_EDGE);
    ~Texture();
  public:
    void Bind(GLuint slot = 0);
    void Unbind();

    inline GLint GetWidth() const;
    inline GLint GetHeight() const;
  private:
    GLuint _id;
    std::string _filepath;
    GLint _width, _height, _BPP;
  };
}
