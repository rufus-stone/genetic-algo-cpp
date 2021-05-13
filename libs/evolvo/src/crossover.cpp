#include "evolvo/crossover.hpp"

#include <random>
#include <spdlog/spdlog.h>

#include "evolvo/chromosome.hpp"
#include "evolvo/utils/exceptions.hpp"

namespace ga
{


auto UniformCrossover::crossover(std::mt19937 &prng, const Chromosome &parent_a, const Chromosome &parent_b) -> Chromosome
{
  // Both parent Chromosomes must be the same length
  if (parent_a.size() != parent_b.size())
  {
    throw ga::xcpt::invalid_parameter("Both parents must have the same length Chromosomes!");
  }

  auto child = ga::Chromosome{};

  std::size_t const gene_count = parent_a.size();

  // Set up a coin flipper
  auto coin_toss = std::uniform_int_distribution<>{0, 1};

  for (std::size_t i = 0; i < gene_count; ++i)
  {
    // Flip a coin
    bool flip = coin_toss(prng) != 0;

    // Heads we take from parent_a
    if (flip)
    {
      child.push_back(parent_a[i]);
    } else // Tails we take from parent_b
    {
      child.push_back(parent_b[i]);
    }
  }

  spdlog::info("Parent A: {}", parent_a);
  spdlog::info("Parent B: {}", parent_b);
  spdlog::info("   Child: {}", child);

  return child;
}

auto UniformCrossover::name() const -> std::string
{
  return "UniformCrossover";
}

} // namespace ga