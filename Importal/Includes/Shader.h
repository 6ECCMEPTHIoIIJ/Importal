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
    class ShaderData
    {
    public:
      ShaderData() = delete;
      ShaderData(const ShaderData&) = delete;
      ShaderData(ShaderData&&) = delete;
      explicit ShaderData(const std::string& shaderFilename);
      void Compile(GLuint shaderType);
      void CompileAsVertex();
      void CompileAsFragment();
      void LinkWith(ShaderData& other);
      GLboolean CheckCompilationStatus() const;
      GLboolean CheckLinkingStatus() const;
      void LogCompilationError() const;
      void LogLinkingError() const;
      GLuint GetLinkedProgram() const;
      ~ShaderData();

    private:
      std::string _rawCode;
      const GLchar* _code;
      GLuint _shader = 0;
      GLuint _program = 0;
    };

  public:
    Shader() = delete;
    Shader(const Shader&) = delete;
    Shader(Shader&&) = delete;
    Shader(const std::string& vShaderFilename, const std::string& fShaderFilename);
    void Use();
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVec2(const std::string& name, const glm::vec2& value) const;
    void SetVec2(const std::string& name, float x, float y) const;
    void SetVec3(const std::string& name, const glm::vec3& value) const;
    void SetVec3(const std::string& name, float x, float y, float z) const;
    void SetVec4(const std::string& name, const glm::vec4& value) const;
    void SetVec4(const std::string& name, float x, float y, float z, float w) const;
    void SetMat2(const std::string& name, const glm::mat2& mat) const;
    void SetMat3(const std::string& name, const glm::mat3& mat) const;
    void SetMat4(const std::string& name, const glm::mat4& mat) const;
    ~Shader();

    static void SetBool(unsigned int layout, bool value);
    static void SetInt(unsigned int layout, int value);
    static void SetFloat(unsigned int layout, float value);
    static void SetVec2(unsigned int layout, const glm::vec2& value);
    static void SetVec2(unsigned int layout, float x, float y);
    static void SetVec3(unsigned int layout, const glm::vec3& value);
    static void SetVec3(unsigned int layout, float x, float y, float z);
    static void SetVec4(unsigned int layout, const glm::vec4& value);
    static void SetVec4(unsigned int layout, float x, float y, float z, float w);
    static void SetMat2(unsigned int layout, const glm::mat2& mat);
    static void SetMat3(unsigned int layout, const glm::mat3& mat);
    static void SetMat4(unsigned int layout, const glm::mat4& mat);

  private:
    GLuint _program;
  };
}