#include "Shader.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <format>

namespace Importal
{
  Shader::ShaderData::ShaderData(const std::string& shaderFilename)
  {
    try
    {
      std::ifstream source(shaderFilename);
      std::stringstream reader;
      reader << source.rdbuf();
      _rawCode = reader.str();
    }
    catch (std::ifstream::failure& e)
    {
      std::cout << std::format("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: {}", e.what()) << std::endl;
    }

    _code = _rawCode.c_str();
  }

  void Shader::ShaderData::Compile(GLuint shaderType)
  {
    _shader = glCreateShader(shaderType);
    glShaderSource(_shader, 1, &_code, NULL);
    glCompileShader(_shader);
  }

  void Shader::ShaderData::CompileAsVertex()
  {
    Compile(GL_VERTEX_SHADER);
  }

  void Shader::ShaderData::CompileAsFragment()
  {
    Compile(GL_FRAGMENT_SHADER);
  }

  void Shader::ShaderData::LinkWith(ShaderData& other)
  {
    other._program = _program = glCreateProgram();
    glAttachShader(_program, _shader);
    glAttachShader(_program, other._shader);
    glLinkProgram(_program);
  }

  GLboolean Shader::ShaderData::CheckCompilationStatus() const
  {
    GLint success;
    glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);
    return success;
  }

  GLboolean Shader::ShaderData::CheckLinkingStatus() const
  {
    GLint success;
    glGetProgramiv(_program, GL_COMPILE_STATUS, &success);
    return success;
  }

  void Shader::ShaderData::LogCompilationError() const
  {
    GLchar infoLog[1024];
    glGetShaderInfoLog(_shader, 1024, NULL, infoLog);
    std::cerr << std::format("ERROR::SHADER_COMPILATION_ERROR\n{}", infoLog) << std::endl;
  }

  void Shader::ShaderData::LogLinkingError() const
  {
    GLchar infoLog[1024];
    glGetProgramInfoLog(_program, 1024, NULL, infoLog);
    std::cerr << std::format("ERROR::PROGRAM_LINKING_ERROR\n{}", infoLog) << std::endl;
  }

  GLuint Shader::ShaderData::GetLinkedProgram() const
  {
    return _program;
  }

  Shader::ShaderData::~ShaderData()
  {
    if (_shader != 0)
      glDeleteShader(_shader);
  }

  Shader::Shader(const std::string& vShaderFilename, const std::string& fShaderFilename)
  {
    ShaderData vShaderData(vShaderFilename);
    ShaderData fShaderData(fShaderFilename);
    vShaderData.CompileAsVertex();
    if (!vShaderData.CheckCompilationStatus())
      vShaderData.LogCompilationError();

    fShaderData.CompileAsFragment();
    if (!fShaderData.CheckCompilationStatus())
      fShaderData.LogCompilationError();

    vShaderData.LinkWith(fShaderData);
    if (!vShaderData.CheckLinkingStatus())
      vShaderData.LogLinkingError();

    _program = vShaderData.GetLinkedProgram();
  }

  void Shader::Use()
  {
    glUseProgram(_program);
  }

  void Shader::SetBool(const std::string& name, bool value) const
  {
    SetBool(glGetUniformLocation(_program, name.c_str()), value);
  }

  void Shader::SetInt(const std::string& name, int value) const
  {
    SetInt(glGetUniformLocation(_program, name.c_str()), value);
  }

  void Shader::SetFloat(const std::string& name, float value) const
  {
    SetFloat(glGetUniformLocation(_program, name.c_str()), (GLfloat)value);
  }

  void Shader::SetVec2(const std::string& name, const glm::vec2& value) const
  {
    SetVec2(glGetUniformLocation(_program, name.c_str()), value);
  }

  void Shader::SetVec2(const std::string& name, float x, float y) const
  {
    SetVec2(glGetUniformLocation(_program, name.c_str()), (GLfloat)x, (GLfloat)y);
  }

  void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
  {
    SetVec3(glGetUniformLocation(_program, name.c_str()), value);
  }

  void Shader::SetVec3(const std::string& name, float x, float y, float z) const
  {
    SetVec3(glGetUniformLocation(_program, name.c_str()), (GLfloat)x, (GLfloat)y, (GLfloat)z);
  }

  void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
  {
    SetVec4(glGetUniformLocation(_program, name.c_str()), value);
  }

  void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const
  {
    SetVec4(glGetUniformLocation(_program, name.c_str()), (GLfloat)x, (GLfloat)y, (GLfloat)z, (GLfloat)w);
  }

  void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const
  {
    SetMat2(glGetUniformLocation(_program, name.c_str()), mat);
  }

  void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const
  {
    SetMat3(glGetUniformLocation(_program, name.c_str()), mat);
  }

  void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const
  {
    SetMat4(glGetUniformLocation(_program, name.c_str()), mat);
  }

  void Shader::SetBool(unsigned int layout, bool value)
  {
    glUniform1i(layout, (GLint)value);
  }

  void Shader::SetInt(unsigned int layout, int value)
  {
    glUniform1i(layout, (GLint)value);
  }

  void Shader::SetFloat(unsigned int layout, float value)
  {
    glUniform1f(layout, (GLfloat)value);
  }

  void Shader::SetVec2(unsigned int layout, const glm::vec2& value)
  {
    glUniform2fv(layout, 1, &value[0]);
  }

  void Shader::SetVec2(unsigned int layout, float x, float y)
  {
    glUniform2f(layout, (GLfloat)x, (GLfloat)y);
  }

  void Shader::SetVec3(unsigned int layout, const glm::vec3& value)
  {
    glUniform3fv(layout, 1, &value[0]);
  }

  void Shader::SetVec3(unsigned int layout, float x, float y, float z)
  {
    glUniform3f(layout, (GLfloat)x, (GLfloat)y, (GLfloat)z);
  }

  void Shader::SetVec4(unsigned int layout, const glm::vec4& value)
  {
    glUniform4fv(layout, 1, &value[0]);
  }

  void Shader::SetVec4(unsigned int layout, float x, float y, float z, float w)
  {
    glUniform4f(layout, (GLfloat)x, (GLfloat)y, (GLfloat)z, (GLfloat)w);
  }

  void Shader::SetMat2(unsigned int layout, const glm::mat2& mat)
  {
    glUniformMatrix2fv(layout, 1, GL_FALSE, &mat[0][0]);
  }

  void Shader::SetMat3(unsigned int layout, const glm::mat3& mat)
  {
    glUniformMatrix3fv(layout, 1, GL_FALSE, &mat[0][0]);
  }

  void Shader::SetMat4(unsigned int layout, const glm::mat4& mat)
  {
    glUniformMatrix4fv(layout, 1, GL_FALSE, &mat[0][0]);
  }

  Shader::~Shader()
  {
    glDeleteProgram(_program);
  }
}