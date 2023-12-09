#include "Shader.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <format>

#include "GlExt.h"

namespace Importal
{
  GLuint Shader::_curProgram = 0;

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
    GL_CALL(glShaderSource(_shader, 1, &_code, NULL));
    GL_CALL(glCompileShader(_shader));
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
    GL_CALL(glAttachShader(_program, _shader));
    GL_CALL(glAttachShader(_program, other._shader));
    GL_CALL(glLinkProgram(_program));
  }

  GLboolean Shader::ShaderData::CheckCompilationStatus() const
  {
    GLint success;
    GL_CALL(glGetShaderiv(_shader, GL_COMPILE_STATUS, &success));
    return success;
  }

  GLboolean Shader::ShaderData::CheckLinkingStatus() const
  {
    GLint success;
    GL_CALL(glGetProgramiv(_program, GL_LINK_STATUS, &success));
    return success;
  }

  void Shader::ShaderData::LogCompilationError() const
  {
    GLchar infoLog[1024];
    GL_CALL(glGetShaderInfoLog(_shader, 1024, NULL, infoLog));
    std::cerr << std::format("ERROR::SHADER_COMPILATION_ERROR\n{}", infoLog) << std::endl;
  }

  void Shader::ShaderData::LogLinkingError() const
  {
    GLchar infoLog[1024];
    GL_CALL(glGetProgramInfoLog(_program, 1024, NULL, infoLog));
    std::cerr << std::format("ERROR::PROGRAM_LINKING_ERROR\n{}", infoLog) << std::endl;
  }

  GLuint Shader::ShaderData::GetLinkedProgram() const
  {
    return _program;
  }

  Shader::ShaderData::~ShaderData()
  {
    if (_shader != 0)
      GL_CALL(glDeleteShader(_shader));
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
    _curProgram = _program;
    GL_CALL(glUseProgram(_program));
  }

  void Shader::SetBool(const std::string& name, bool value)
  {
    SetBool(glGetUniformLocation(_curProgram, name.c_str()), value);
  }

  void Shader::SetInt(const std::string& name, int value)
  {
    SetInt(glGetUniformLocation(_curProgram, name.c_str()), value);
  }

  void Shader::SetFloat(const std::string& name, float value)
  {
    SetFloat(glGetUniformLocation(_curProgram, name.c_str()), (GLfloat)value);
  }

  void Shader::SetVec2(const std::string& name, const glm::vec2& value)
  {
    SetVec2(glGetUniformLocation(_curProgram, name.c_str()), value);
  }

  void Shader::SetVec2(const std::string& name, float x, float y)
  {
    SetVec2(glGetUniformLocation(_curProgram, name.c_str()), (GLfloat)x, (GLfloat)y);
  }

  void Shader::SetVec3(const std::string& name, const glm::vec3& value)
  {
    SetVec3(glGetUniformLocation(_curProgram, name.c_str()), value);
  }

  void Shader::SetVec3(const std::string& name, float x, float y, float z)
  {
    SetVec3(glGetUniformLocation(_curProgram, name.c_str()), (GLfloat)x, (GLfloat)y, (GLfloat)z);
  }

  void Shader::SetVec4(const std::string& name, const glm::vec4& value)
  {
    SetVec4(glGetUniformLocation(_curProgram, name.c_str()), value);
  }

  void Shader::SetVec4(const std::string& name, float x, float y, float z, float w)
  {
    SetVec4(glGetUniformLocation(_curProgram, name.c_str()), (GLfloat)x, (GLfloat)y, (GLfloat)z, (GLfloat)w);
  }

  void Shader::SetMat2(const std::string& name, const glm::mat2& mat)
  {
    SetMat2(glGetUniformLocation(_curProgram, name.c_str()), mat);
  }

  void Shader::SetMat3(const std::string& name, const glm::mat3& mat)
  {
    SetMat3(glGetUniformLocation(_curProgram, name.c_str()), mat);
  }

  void Shader::SetMat4(const std::string& name, const glm::mat4& mat)
  {
    SetMat4(glGetUniformLocation(_curProgram, name.c_str()), mat);
  }

  void Shader::SetBool(int layout, bool value)
  {
    GL_CALL(glUniform1i(layout, (GLint)value));
  }

  void Shader::SetInt(int layout, int value)
  {
    GL_CALL(glUniform1i(layout, (GLint)value));
  }

  void Shader::SetFloat(int layout, float value)
  {
    GL_CALL(glUniform1f(layout, (GLfloat)value));
  }

  void Shader::SetVec2(int layout, const glm::vec2& value)
  {
    GL_CALL(glUniform2fv(layout, 1, glm::value_ptr(value)));
  }

  void Shader::SetVec2(int layout, float x, float y)
  {
    GL_CALL(glUniform2f(layout, (GLfloat)x, (GLfloat)y));
  }

  void Shader::SetVec3(int layout, const glm::vec3& value)
  {
    GL_CALL(glUniform3fv(layout, 1, glm::value_ptr(value)));
  }

  void Shader::SetVec3(int layout, float x, float y, float z)
  {
    GL_CALL(glUniform3f(layout, (GLfloat)x, (GLfloat)y, (GLfloat)z));
  }

  void Shader::SetVec4(int layout, const glm::vec4& value)
  {
    GL_CALL(glUniform4fv(layout, 1, glm::value_ptr(value)));
  }

  void Shader::SetVec4(int layout, float x, float y, float z, float w)
  {
    GL_CALL(glUniform4f(layout, (GLfloat)x, (GLfloat)y, (GLfloat)z, (GLfloat)w));
  }

  void Shader::SetMat2(int layout, const glm::mat2& mat)
  {
    GL_CALL(glUniformMatrix2fv(layout, 1, GL_FALSE, glm::value_ptr(mat)));
  }

  void Shader::SetMat3(int layout, const glm::mat3& mat)
  {
    GL_CALL(glUniformMatrix3fv(layout, 1, GL_FALSE, glm::value_ptr(mat)));
  }

  void Shader::SetMat4(int layout, const glm::mat4& mat)
  {
    GL_CALL(glUniformMatrix4fv(layout, 1, GL_FALSE, glm::value_ptr(mat)));
  }

  Shader::~Shader()
  {
    GL_CALL(glDeleteProgram(_program));
  }
}