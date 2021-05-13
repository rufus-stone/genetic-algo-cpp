#include "evolvo/ga.hpp"

#include <algorithm>
#include <numeric>

#include <spdlog/spdlog.h>

namespace ga
{

// Construct a Network from a vector of Layers
GeneticAlgorithm::GeneticAlgorithm(int i) : m_i(i)
{
  spdlog::info("this->m_i: {}", this->m_i);
}

} // namespace ga
