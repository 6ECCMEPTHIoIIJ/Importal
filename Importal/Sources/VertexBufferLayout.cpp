#include "VertexBufferLayout.h"
#include <stdexcept>

namespace Importal {
		const std::vector<VBElement>& VertexBufferLayout::GetElements() const
		{
				return _elements;
		}
		void Importal::VertexBufferLayout::Push(GLuint type, GLuint count, GLint normalized)
		{
				_elements.push_back({ type, count, normalized });
				_stride += VBElement::GetTypeSize(type);
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
