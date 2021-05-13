#pragma once

#include <random>

namespace ga
{

class GeneticAlgorithm
{
private:
  //std::vector<nn::Layer> m_layers;
  int m_i;

public:
  GeneticAlgorithm() = delete;

  // Construct a GeneticAlgorithm with the specified SelectionMethod, CrossoverMethod, and MutationMethod
  explicit GeneticAlgorithm(int i);

  // Propogate the inputs through each Layer, and return the results
  //auto evolve(std::mt19937 &prng, POPULATION???) -> std::vector<double>;
};

} // namespace ga
