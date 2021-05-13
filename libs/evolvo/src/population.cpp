#include "evolvo/population.hpp"

#include <algorithm>
#include <iterator>

namespace ga
{

[[nodiscard]] auto Population::fitnesses() const -> std::vector<double>
{
  auto output = std::vector<double>{};

  std::transform(std::begin(*this), std::end(*this), std::back_inserter(output), [](auto const &individual) { return individual.fitness(); });

  return output;
}

} // namespace ga