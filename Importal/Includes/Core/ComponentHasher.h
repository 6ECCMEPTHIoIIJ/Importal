#pragma once
#include <cstddef>

namespace Importal::Core {
  class ComponentHasher {
  public:
    using Hash = std::size_t;

    template<class T>
    Hash operator()(const T& key) const
    {
      static_assert(std::is_base_of_v<GameComponent, T>);

      return typeid(key).hash_code();
    }

    template<class T>
    Hash operator()() const
    {
      static_assert(std::is_base_of_v<GameComponent, T>);

      return typeid(T).hash_code();
    }
  };
}
