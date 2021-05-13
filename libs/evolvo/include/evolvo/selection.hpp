#pragma once

#include <random>
#include <vector>

namespace ga
{

class SelectionMethod
{
public:
  virtual auto select(std::mt19937 &prng, std::vector<int> const &population) -> int = 0;
};

} // namespace ga