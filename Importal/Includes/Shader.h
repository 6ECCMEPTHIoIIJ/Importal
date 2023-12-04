#pragma once

#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
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

    void setVec2(const std::string& name, const glm::vec2& value) const;

    void setVec2(const std::string& name, float x, float y) const;
    // ------------------------------------------------------------------------
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    // ------------------------------------------------------------------------
    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setVec4(const std::string& name, float x, float y, float z, float w) const;
    // ------------------------------------------------------------------------
    void setMat2(const std::string& name, const glm::mat2& mat) const;
    // ------------------------------------------------------------------------
    void setMat3(const std::string& name, const glm::mat3& mat) const;
    // ------------------------------------------------------------------------
    void setMat4(const std::string& name, const glm::mat4& mat) const;

  private:
      // utility function for checking shader compilation/linking errors.
      // ------------------------------------------------------------------------
    void CheckCompileErrors(unsigned int shader, std::string type);
  };
}