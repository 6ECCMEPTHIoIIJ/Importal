#pragma once
#include "GlExt.h"

namespace Importal
{
  class Texture
  {
  public:
    struct TextureData
    {
      unsigned int id;
      std::string type;
      std::string path;
    };
    
    Texture(const std::string& path,
            const std::string& type,
            GLint MIN_FILTER = GL_LINEAR,
            GLint MAG_FILTER = GL_LINEAR,
            GLint WRAP_S = GL_CLAMP_TO_EDGE,
            GLint WRAP_T = GL_CLAMP_TO_EDGE);

    Texture(const TextureData& data,
            GLint MIN_FILTER = GL_LINEAR,
            GLint MAG_FILTER = GL_LINEAR,
            GLint WRAP_S = GL_CLAMP_TO_EDGE,
            GLint WRAP_T = GL_CLAMP_TO_EDGE);
  
  public:
    void Bind(GLuint slot = 0);
    static void Unbind();
    void Delete();

    inline GLint GetWidth() const;
    inline GLint GetHeight() const;
    inline GLuint GetID() const;
    const std::string& GetType() const;
    const std::string& GetPath() const;
  private:
    GLint _width, _height, _BPP;
    TextureData _data;
  };
}
