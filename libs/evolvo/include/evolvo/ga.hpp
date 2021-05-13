#pragma once

#include <random>

#include "evolvo/population.hpp"
#include "evolvo/selection.hpp"
#include "evolvo/crossover.hpp"

namespace ga
{

class GeneticAlgorithm
{
private:
  std::unique_ptr<SelectionMethod> m_selection_method;
  std::unique_ptr<CrossoverMethod> m_crossover_method;
  //std::unique_ptr<MutationMethod> m_mutation_method;

public:
  GeneticAlgorithm() = delete;

  // Construct a GeneticAlgorithm with the specified SelectionMethod, CrossoverMethod, and MutationMethod
  explicit GeneticAlgorithm(std::unique_ptr<SelectionMethod> selection_method, std::unique_ptr<CrossoverMethod> crossover_method /*, std::unique_ptr<MutationMethod> mutation_method*/);

  // Propogate the inputs through each Layer, and return the results
  auto evolve(std::mt19937 &prng, Population const &population) -> std::vector<double>;
};

} // namespace ga
