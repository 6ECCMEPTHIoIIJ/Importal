#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Importal
{
  Texture::Texture(const std::string& path,
                   GLint MIN_FILTER,
                   GLint MAG_FILTER,
                   GLint WRAP_S,
                   GLint WRAP_T)
  {
    stbi_set_flip_vertically_on_load(1);
    stbi_uc* buffer = stbi_load(path.c_str(), &_width, &_height, &_BPP, 4);

    GL_CALL(glGenTextures(1, &_id));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, _id));

    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MIN_FILTER));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MAG_FILTER));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WRAP_S));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WRAP_T));

    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer));

    Unbind();
    if (buffer)
      stbi_image_free(buffer);
  }

  Texture::~Texture()
  {
    GL_CALL(glDeleteTextures(1, &_id));
  }

  void Texture::Bind(GLuint slot)
  {
    GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, _id));
  }

  void Texture::Unbind()
  {
    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
  }

  inline GLint Texture::GetWidth() const
  {
    return _width;
  }

  inline GLint Texture::GetHeight() const
  {
    return _height;
  }
}
