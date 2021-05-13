#include "evolvo/selection.hpp"

#include <spdlog/spdlog.h>

namespace ga
{


auto RouletteWheelSelection::select(std::mt19937 &prng, Population const &population) -> std::size_t
{
  auto const fitnesses = population.fitnesses();
  std::discrete_distribution<std::size_t> weighted_choice(std::begin(fitnesses), std::end(fitnesses));

  return weighted_choice(prng);
}

auto RouletteWheelSelection::name() const -> std::string
{
  return "RouletteWheelSelection";
}

} // namespace ga