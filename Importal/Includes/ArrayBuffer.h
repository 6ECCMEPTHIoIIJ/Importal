#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Importal
{
  class ArrayBuffer
  {
  public:
    ArrayBuffer(unsigned int count = 1);
    void Bind();
    void AddBuffer(VertexBuffer& vb, const VertexBufferLayout& vb_layout);
    ~ArrayBuffer();

    static void Unbind();
  private:
    GLuint _id;
    unsigned int _count;
    GLuint _currentAttribIndex = 0;
  };
}