#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Importal
{
  class ArrayBuffer
  {
  public:
    ArrayBuffer(unsigned int count = 1);
    void Bind();
    ~ArrayBuffer();

    static void Unbind();
  private:
    GLuint _id;
    unsigned int _count;
  };
}