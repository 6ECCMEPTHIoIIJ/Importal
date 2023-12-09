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
    static void SetBool(const std::string& name, bool value);
    static void SetInt(const std::string& name, int value);
    static void SetFloat(const std::string& name, float value);
    static void SetVec2(const std::string& name, const glm::vec2& value);
    static void SetVec2(const std::string& name, float x, float y);
    static void SetVec3(const std::string& name, const glm::vec3& value);
    static void SetVec3(const std::string& name, float x, float y, float z);
    static void SetVec4(const std::string& name, const glm::vec4& value);
    static void SetVec4(const std::string& name, float x, float y, float z, float w);
    static void SetMat2(const std::string& name, const glm::mat2& mat);
    static void SetMat3(const std::string& name, const glm::mat3& mat);
    static void SetMat4(const std::string& name, const glm::mat4& mat);
    ~Shader();

    static void SetBool(int layout, bool value);
    static void SetInt(int layout, int value);
    static void SetFloat(int layout, float value);
    static void SetVec2(int layout, const glm::vec2& value);
    static void SetVec2(int layout, float x, float y);
    static void SetVec3(int layout, const glm::vec3& value);
    static void SetVec3(int layout, float x, float y, float z);
    static void SetVec4(int layout, const glm::vec4& value);
    static void SetVec4(int layout, float x, float y, float z, float w);
    static void SetMat2(int layout, const glm::mat2& mat);
    static void SetMat3(int layout, const glm::mat3& mat);
    static void SetMat4(int layout, const glm::mat4& mat);

  private:
    GLuint _program;
    static GLuint _curProgram;
  };
}