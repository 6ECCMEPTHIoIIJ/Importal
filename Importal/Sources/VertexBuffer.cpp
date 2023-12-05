#include "VertexBuffer.h"

namespace Importal
{
  VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int drawMode)
  {
    glGenBuffers(1, &_id);
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, size, data, drawMode);
  }

  void VertexBuffer::Bind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, _id);
  }

  void VertexBuffer::Unbind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  VertexBuffer::~VertexBuffer()
  {
    glDeleteBuffers(1, &_id);
  }
}