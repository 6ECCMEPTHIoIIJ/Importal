#include "Core/BaseComponents/Transform.h"

Importal::Core::Transform::Transform(Importal::Core::GameObject* parent, Transform* transform) : GameComponent(parent)
{
}

Importal::Core::Transform::Transform(Importal::Core::GameObject* parent, glm::vec3 position) : GameComponent(parent)
{
}
