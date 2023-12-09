#include "VertexBuffer.h"

#include "GlExt.h"

namespace Importal
{
  VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int drawMode)
  {
    GL_CALL(glGenBuffers(1, &_id));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, _id));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, drawMode));
  }

  void VertexBuffer::Bind()
  {
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, _id));
  }

  void VertexBuffer::Unbind()
  {
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
  }

  VertexBuffer::~VertexBuffer()
  {
    GL_CALL(glDeleteBuffers(1, &_id));
  }
}