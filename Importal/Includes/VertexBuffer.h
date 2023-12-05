#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Importal
{
  class VertexBuffer
  {
  public:
    VertexBuffer(const void* data, unsigned int size, unsigned int drawMode);
    void Bind();
    ~VertexBuffer();

    static void Unbind();

  private:
    GLuint _id;
  };
}