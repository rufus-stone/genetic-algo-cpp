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

  // Construct an Individual from a fitness
  explicit Individual(double const &fitness);

  // Construct an Individual from a Chromosome and a fitness
  Individual(Chromosome const &chromosome, double const &fitness);

  // Getters
  [[nodiscard]] virtual auto fitness() const -> double;
  [[nodiscard]] virtual auto chromosome() const -> Chromosome const &;
};

} // namespace ga