#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Importal
{
  class IndexBuffer
  {
  public:
    IndexBuffer(const unsigned int* data, unsigned int count, unsigned int drawMode);
    // IndexBuffer(const IndexBuffer&) = delete;
    // IndexBuffer(IndexBuffer&&) = delete;
    void Bind();
    unsigned int GetCount() const;
    ~IndexBuffer();

    static void Unbind();
  private:
    GLuint _id;
    unsigned int _count;
  };
}