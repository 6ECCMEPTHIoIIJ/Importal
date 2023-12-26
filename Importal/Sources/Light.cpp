#include "Light.h"

Light::Light(const Type& type) :
  m_ambienceColor(1.f, 1.f, 1.f),
  m_specularColor(1.f, 1.f, 1.f),
  m_diffuseColor(1.f, 1.f, 1.f),
  m_position(0.f, 0.f, 0.f, 1.f),
  m_direction(0.f, 0.f, 1.f, 0.f),
  m_cutoff(glm::half_pi<float>()),
  m_power(1.0f),
  m_type(type)
{
  m_lightMatrix = glm::identity<glm::mat4>();
  m_lightMatrix = glm::lookAt(glm::vec3(m_position),
                       glm::vec3(m_position - m_direction),
                       glm::vec3(0.0f, 1.0f, 0.0f));
}

void Light::setAmbienceColor(const glm::vec3& ambienceColor)
{
  m_ambienceColor = ambienceColor;
}

const glm::vec3& Light::getAmbienceColor() const
{
  return m_ambienceColor;
}

void Light::setDiffuseColor(const glm::vec3& diffuseColor)
{
  m_diffuseColor = diffuseColor;
}

const glm::vec3& Light::getDiffuseColor() const
{
  return m_diffuseColor;
}

void Light::setSpecularColor(const glm::vec3& specularColor)
{
  m_specularColor = specularColor;
}

const glm::vec3& Light::getSpecularColor() const
{
  return m_specularColor;
}

void Light::setPosition(const glm::vec4& position)
{
  m_position = position;
  m_lightMatrix = glm::identity<glm::mat4>();
  m_lightMatrix = glm::lookAt(glm::vec3(m_position),
                       glm::vec3(m_position) - _front,
                       glm::vec3(0.0f, 1.0f, 0.0f));
}

const glm::vec4& Light::getPosition() const
{
  return m_position;
}

void Light::setDirection(const glm::vec4& direction)
{
  _front = glm::normalize(glm::vec3(cos(
    glm::radians(direction.y)) * cos(glm::radians(direction.x)),
    sin(glm::radians(direction.x)),
    sin(glm::radians(direction.y)) * cos(glm::radians(direction.x))));

  m_direction = direction;
  m_direction = glm::normalize(m_direction);
  m_lightMatrix = glm::identity<glm::mat4>();
  m_lightMatrix = glm::lookAt(glm::vec3(m_position),
                       glm::vec3(m_position) - _front,
                       glm::vec3(0.0f, 1.0f, 0.0f));
}

const glm::vec4& Light::getDirection() const
{
  return m_direction;
}

void Light::setCutoff(const float cutoff)
{
  m_cutoff = cutoff;
}

float Light::getCutoff() const
{
  return m_cutoff;
}

void Light::setType(const Light::Type& type)
{
  m_type = type;
}

const Light::Type& Light::getType() const
{
  return m_type;
}


float Light::getPower() const
{
  return m_power;
}

void Light::setPower(float power)
{
  m_power = power;
}


const glm::mat4& Light::getLightMatrix() const
{
  return m_lightMatrix;
}