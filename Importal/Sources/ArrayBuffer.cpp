#include "ArrayBuffer.h"

namespace Importal
{
  ArrayBuffer::ArrayBuffer(unsigned int count)
    : _count(count)
  {
    glGenVertexArrays(count, &_id);
  }

  void ArrayBuffer::Bind()
  {
    glBindVertexArray(_id);
  }

  ArrayBuffer::~ArrayBuffer()
  {
    glDeleteVertexArrays(_count, &_id);
  }

  void ArrayBuffer::Unbind()
  {
    glBindVertexArray(0);
  }
}