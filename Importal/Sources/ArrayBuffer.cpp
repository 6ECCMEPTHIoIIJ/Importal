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

  void ArrayBuffer::AddBuffer(VertexBuffer& vb, const VertexBufferLayout& vb_layout)
  {
      vb.Bind();
      const auto& elements = vb_layout.GetElements();
      GLuint offset = 0;
      for (GLuint i = 0; i < elements.size(); i++)
      {
          const auto& element = elements[i];
          GL_CALL(glEnableVertexAttribArray(_currentAttribIndex));
          GL_CALL(glVertexAttribPointer(_currentAttribIndex, element.count, element.type, element.normalized, 
              vb_layout.GetStride(), (const void*)(offset)));
          offset += element.count * VBElement::GetTypeSize(element.type);
        ++_currentAttribIndex;
      }
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
