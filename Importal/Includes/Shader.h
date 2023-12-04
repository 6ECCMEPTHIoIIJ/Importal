#pragma once

#include <GL/glew.h>
#include <string>

namespace Importal
{
  class Shader
  {
  public:
    unsigned int Program;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // activate the shader
    // ------------------------------------------------------------------------
    void Use();
    // utility uniform functions
    // ------------------------------------------------------------------------
    void SetBool(const std::string& name, bool value) const;
    // ------------------------------------------------------------------------
    void SetInt(const std::string& name, int value) const;
    // ------------------------------------------------------------------------
    void SetFloat(const std::string& name, float value) const;

  private:
      // utility function for checking shader compilation/linking errors.
      // ------------------------------------------------------------------------
    void CheckCompileErrors(unsigned int shader, std::string type);
  };
}