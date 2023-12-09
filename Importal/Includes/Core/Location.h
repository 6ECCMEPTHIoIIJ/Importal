#pragma once

namespace Importal::Core {
  class Location
  {
  public:
    Location();

    void AddGameObject(GameObject* object);
    void RemoveGameObject(GameObject* object);

    void Tick(double deltaTime);
    void Render();

#pragma region Removed ctors

    Location(const Location&) = delete;
    Location(Location&&) = delete;

#pragma endregion

  private:
    std::vector<GameObject> _gameObjects = std::vector<GameObject>();
  };
}


