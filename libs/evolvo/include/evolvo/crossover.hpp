#pragma once

#include <random>
#include <vector>
#include <string>

#include "evolvo/chromosome.hpp"

namespace ga
{

// Pure virtual base class for implementing a crossover method
class CrossoverMethod
{
public:
  virtual ~CrossoverMethod() = default;
  CrossoverMethod() = default;
  CrossoverMethod(CrossoverMethod const &) = default;
  CrossoverMethod &operator=(CrossoverMethod const &) = default;
  CrossoverMethod(CrossoverMethod &&) = default;
  CrossoverMethod &operator=(CrossoverMethod &&) = default;

  [[nodiscard]] virtual auto name() const -> std::string = 0;
  [[nodiscard]] virtual auto crossover(std::mt19937 &prng, Chromosome const &parent_a, Chromosome const &parent_b) -> Chromosome = 0;
};

// Uniform crossover
class UniformCrossover : public CrossoverMethod
{
public:
  [[nodiscard]] auto name() const -> std::string override;
  [[nodiscard]] auto crossover(std::mt19937 &prng, Chromosome const &parent_a, Chromosome const &parent_b) -> Chromosome override;
};

} // namespace ga
