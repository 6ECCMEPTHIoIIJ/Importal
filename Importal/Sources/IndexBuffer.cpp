#include "IndexBuffer.h"

#include "GlExt.h"

namespace Importal
{
  IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count, unsigned int drawMode)
    : _count(count)
  {
    GL_CALL(glGenBuffers(1, &_id));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(*data), data, drawMode));
  }

  void IndexBuffer::Bind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
  }

  void IndexBuffer::Unbind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  unsigned int IndexBuffer::GetCount() const
  {
    return _count;
  }

  IndexBuffer::~IndexBuffer()
  {
    GL_CALL(glDeleteBuffers(1, &_id));
  }
}