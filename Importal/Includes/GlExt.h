#pragma once

#include <GL/glew.h>
#include <format>
#include <iostream>

#define ASSERT(COND) if(!(COND)) __debugbreak();

#define GL_CALL(GL_CODE) Importal::GlClearErrors();\
GL_CODE;\
ASSERT(Importal::GlCheckErrors(#GL_CODE, __FILE__, __LINE__))

namespace Importal
{
  void GlClearErrors();
  bool GlCheckErrors(const char* func, const char* file, int line);
}