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

  void ArrayBuffer::AddBuffer(VertexBuffer& vb, const VertexBufferLayout& vb_layout)
  {
      vb.Bind();
      const auto& elements = vb_layout.GetElements();
      GLuint offset = 0;
      for (GLuint i = 0; i < elements.size(); i++)
      {
          const auto& element = elements[i];
          
      }
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