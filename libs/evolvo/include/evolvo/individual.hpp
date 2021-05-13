#pragma once

#include <random>
#include <vector>

#include "evolvo/chromosome.hpp"

namespace ga
{

class Individual
{

private:
  Chromosome m_chromosome;
  double m_fitness;

public:
  Individual() = delete;

  // Construct an Individual from a Chromosome
  explicit Individual(Chromosome const &chromosome);

  // Getters
  [[nodiscard]] auto fitness() const -> double;
  [[nodiscard]] auto chromosome() const -> Chromosome const &;
};

} // namespace ga