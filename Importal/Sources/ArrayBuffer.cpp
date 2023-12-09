#include "ArrayBuffer.h"

#include "GlExt.h"

namespace Importal
{
  ArrayBuffer::ArrayBuffer(unsigned int count)
    : _count(count)
  {
    GL_CALL(glGenVertexArrays(count, &_id));
  }

  void ArrayBuffer::Bind()
  {
    GL_CALL(glBindVertexArray(_id));
  }

  ArrayBuffer::~ArrayBuffer()
  {
    GL_CALL(glDeleteVertexArrays(_count, &_id));
  }

  void ArrayBuffer::Unbind()
  {
    GL_CALL(glBindVertexArray(0));
  }
}