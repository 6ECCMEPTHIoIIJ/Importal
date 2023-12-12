#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Importal
{
  Texture::Texture(const std::string& path, const std::string& type, GLint MIN_FILTER, GLint MAG_FILTER, GLint WRAP_S,
    GLint WRAP_T) : _data{}
  {
    _data.path = path;
    _data.type = type;
    
    // stbi_set_flip_vertically_on_load(1);
    stbi_uc* buffer = stbi_load(path.c_str(), &_width, &_height, &_BPP, 0);

    GL_CALL(glGenTextures(1, &_data.id));
    Bind();

    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MIN_FILTER));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MAG_FILTER));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WRAP_S));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WRAP_T));

    GLenum format = GL_RGBA;
    switch (_BPP)
    {
    case 1:
      format = GL_RED;
      break;
    case 3:
      format = GL_RGB;
      break;
    case 4:
      format = GL_RGBA;
      break;
    }
    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, format, _width, _height, 0, format, GL_UNSIGNED_BYTE, buffer));

    Unbind();
    if (buffer)
      stbi_image_free(buffer);
  }

  Texture::Texture(const TextureData& data, GLint MIN_FILTER, GLint MAG_FILTER, GLint WRAP_S, GLint WRAP_T)
    : Texture(data.path, data.type, MIN_FILTER, MAG_FILTER, WRAP_S, WRAP_T)
  {
  }

  void Texture::Bind(GLuint slot)
  {
    GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, _data.id));
  }

  void Texture::Unbind()
  {
    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
  }

  void Texture::Delete()
  {
    GL_CALL(glDeleteTextures(1, &_data.id));
  }

  inline GLint Texture::GetWidth() const
  {
    return _width;
  }

  inline GLint Texture::GetHeight() const
  {
    return _height;
  }

  GLuint Texture::GetID() const
  {
    return _data.id;
  }

  const std::string& Texture::GetType() const
  {
    return _data.type;
  }

  const std::string& Texture::GetPath() const
  {
    return _data.path;
  }
}
