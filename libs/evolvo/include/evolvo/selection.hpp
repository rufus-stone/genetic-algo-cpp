#pragma once

#include <random>
#include <vector>
#include <string>

#include "evolvo/individual.hpp"
#include "evolvo/population.hpp"

namespace ga
{

// Pure virtual base class for implementing a selection method
class SelectionMethod
{
public:
  virtual ~SelectionMethod() = default;
  SelectionMethod() = default;
  SelectionMethod(SelectionMethod const &) = default;
  SelectionMethod &operator=(SelectionMethod const &) = default;
  SelectionMethod(SelectionMethod &&) = default;
  SelectionMethod &operator=(SelectionMethod &&) = default;

  [[nodiscard]] virtual auto name() const -> std::string = 0;
  [[nodiscard]] virtual auto select(std::mt19937 &prng, Population const &population) -> std::size_t = 0;
};

// Roulette wheel selection that uses the fitness scores of all Individuals in the Population as weights to determine the likelihood that a given Individual will be chosen
class RouletteWheelSelection : public SelectionMethod
{
public:
  [[nodiscard]] auto name() const -> std::string override;
  [[nodiscard]] auto select(std::mt19937 &prng, Population const &population) -> std::size_t override;
};

} // namespace ga
