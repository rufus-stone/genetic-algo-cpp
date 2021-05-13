#include "evolvo/ga.hpp"

#include <algorithm>
#include <numeric>

#include <spdlog/spdlog.h>

namespace ga
{

// Construct a Network from a vector of Layers
GeneticAlgorithm::GeneticAlgorithm(std::unique_ptr<SelectionMethod> selection_method, std::unique_ptr<CrossoverMethod> crossover_method) : m_selection_method(std::move(selection_method)), m_crossover_method(std::move(crossover_method))
{
  spdlog::info("Selection method: {}", this->m_selection_method->name());
  spdlog::info("Crossover method: {}", this->m_crossover_method->name());
}

} // namespace ga
