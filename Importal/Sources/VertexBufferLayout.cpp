#include "VertexBufferLayout.h"
#include <stdexcept>

namespace Importal 
{
		const std::vector<VBElement>& VertexBufferLayout::GetElements() const
		{
				return _elements;
		}
		GLuint VertexBufferLayout::GetStride() const
		{
				return _stride;
		}
		void Importal::VertexBufferLayout::Push(GLuint type, GLuint count, GLubyte normalized)
		{
				_elements.push_back({ type, count, normalized });
				_stride += VBElement::GetTypeSize(type) * count;
		}

		unsigned int Importal::VBElement::GetTypeSize(GLuint type)
		{
				switch (type)
				{
				case GL_FLOAT: return sizeof(GLfloat);
				case GL_UNSIGNED_INT: return sizeof(GLuint);
				case GL_UNSIGNED_BYTE: return sizeof(GLbyte);
				default:
						throw std::invalid_argument("Invalid type");
				}
		}
}
