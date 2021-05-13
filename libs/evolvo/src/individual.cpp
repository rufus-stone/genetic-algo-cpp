#include "evolvo/individual.hpp"
#include "evolvo/chromosome.hpp"

#include <spdlog/spdlog.h>

namespace ga
{

// Construct an Individual from a Chromosome
Individual::Individual(Chromosome const &chromosome) : m_chromosome(chromosome), m_fitness(0.0)
{
  spdlog::info("Individual: {} / {}", this->m_fitness, this->m_chromosome);
}

// Construct an Individual from a fitness
Individual::Individual(double const &fitness) : m_chromosome({}), m_fitness(fitness)
{
  spdlog::info("Individual: {} / {}", this->m_fitness, this->m_chromosome);
}

// Construct an Individual from a Chromosome and a fitness
Individual::Individual(Chromosome const &chromosome, double const &fitness) : m_chromosome(chromosome), m_fitness(fitness)
{
  spdlog::info("Individual: {} / {}", this->m_fitness, this->m_chromosome);
}

auto Individual::fitness() const -> double
{
  return this->m_fitness;
}

auto Individual::chromosome() const -> Chromosome const &
{
  return this->m_chromosome;
}

} // namespace ga
