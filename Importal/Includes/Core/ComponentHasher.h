#pragma once
#include <cstddef>
#include <type_traits>
#include "GameComponent.h"

namespace Importal::Core {
  class ComponentHasher {
  public:
    using Hash = std::size_t;

    template<class T>
      requires std::is_base_of_v<GameComponent, T>
    Hash operator()(const T& key) const
    {
      return typeid(key).hash_code();
    }

    template<class T>
      requires std::is_base_of_v<GameComponent, T>
    Hash operator()() const
    {
      return typeid(T).hash_code();
    }
  };
}
