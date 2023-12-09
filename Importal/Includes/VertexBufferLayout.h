#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

namespace Importal 
{
		struct VBElement
		{
				GLuint type;
				GLuint count;
				GLubyte normalized;

				static unsigned int GetTypeSize(GLuint type);
		};

		class VertexBufferLayout
		{
		public:
				VertexBufferLayout() = default;
				~VertexBufferLayout() = default;

				const std::vector<VBElement>& GetElements() const;
				GLuint GetStride() const;

		public:
				void Push(GLuint count, GLuint type, GLubyte normalized = 0);
		private:
				std::vector<VBElement> _elements;
				GLuint _stride{ 0 };
		};
		
}