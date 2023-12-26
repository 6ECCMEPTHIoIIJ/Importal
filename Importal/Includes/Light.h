#pragma once

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

class Light
{
public:
  enum Type {
    Directional = 0,
    Point = 1,
    Spot = 2,
  };

  Light(const Type& type = Directional);

  void setAmbienceColor(const glm::vec3& ambienceColor);
  const glm::vec3& getAmbienceColor() const;
  void setDiffuseColor(const glm::vec3& diffuseColor);
  const glm::vec3& getDiffuseColor() const;
  void setSpecularColor(const glm::vec3& specularColor);
  const glm::vec3& getSpecularColor() const;

  void setPosition(const glm::vec4& position);
  const glm::vec4& getPosition() const;
  void setDirection(const glm::vec4& direction);
  const glm::vec4& getDirection() const;
  void setCutoff(const float cutoff);
  float getCutoff() const;
  float getPower() const;
  void setPower(const float power);

  void setType(const Type& type);
  const Type& getType() const;

  const glm::mat4& getLightMatrix() const;

private:
  glm::vec3 m_ambienceColor;
  glm::vec3 m_diffuseColor;
  glm::vec3 m_specularColor;

  glm::vec4 m_position;
  glm::vec4 m_direction;
  float m_cutoff;
  float m_power;
  glm::vec3 _front;

  Type m_type;
  glm::mat4 m_lightMatrix;
};
