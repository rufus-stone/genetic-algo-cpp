#include "evolvo/chromosome.hpp"
#include "evolvo/crossover.hpp"
#include "evolvo/individual.hpp"
#include "evolvo/population.hpp"
#include "evolvo/selection.hpp"
#define CATCH_CONFIG_MAIN // This tells the Catch2 header to generate a main

#include "catch.hpp"

#include <random>
#include <vector>
#include <map>

#include <spdlog/spdlog.h>

#include <evolvo/ga.hpp>

////////////////////////////////////////////////////////////////
TEST_CASE("Chromosome", "[ga][chromosome]")
{
  auto const chromo = ga::Chromosome{{1.1, 2.0, -3.3, 4.6}};

  REQUIRE_THAT(chromo, Catch::Matchers::Approx(std::vector<double>{1.1, 2.0, -3.3, 4.6}));
  REQUIRE(chromo[0] == Approx(1.1));
  REQUIRE(chromo.size() == 4);
}

////////////////////////////////////////////////////////////////
TEST_CASE("Individual", "[ga][individual]")
{
  // Create a Chromosome and a fitness
  auto const chromo = ga::Chromosome{{1.1, 2.0, -3.3, 4.6}};
  double const fitness = 1.0;

  // Create a new Individual from the Chromosome
  auto const individual1 = ga::Individual{chromo};

  // Check that it was created correctly
  REQUIRE(individual1.chromosome() == chromo);
  REQUIRE_THAT(individual1.chromosome(), Catch::Matchers::Approx(std::vector<double>{1.1, 2.0, -3.3, 4.6}));
  REQUIRE(individual1.fitness() == 0.0);


  // Create a new Individual from the fitness
  auto const individual2 = ga::Individual{fitness};

  // Check that it was created correctly
  REQUIRE(individual2.chromosome().empty() == true);
  REQUIRE(individual2.fitness() == 1.0);


  // Create a new Individual from the Chromosome and the fitness
  auto const individual3 = ga::Individual{chromo, fitness};

  // Check that it was created correctly
  REQUIRE(individual3.chromosome() == chromo);
  REQUIRE_THAT(individual3.chromosome(), Catch::Matchers::Approx(std::vector<double>{1.1, 2.0, -3.3, 4.6}));
  REQUIRE(individual3.fitness() == 1.0);
}

////////////////////////////////////////////////////////////////
TEST_CASE("Selection", "[ga][individual]")
{
  // Seed an mt19937 prng for a predictable "random" number to use for testing
  auto prng = std::mt19937{42};

  // Create a RouletteWheelSelection SelectionMethod
  auto roulette_wheel = ga::RouletteWheelSelection{};

  // Create a new Population from a collection of Individuals with the specified fitnesses to ride the wheel
  auto const population = ga::Population{{ga::Individual{2.0}, ga::Individual{1.0}, ga::Individual{4.0}, ga::Individual{3.0}}};

  // Spin the wheel 1000 times and see how many times each individual is chosen
  auto results = std::map<int, int>{};
  constexpr std::size_t spins = 1000;
  for (std::size_t i = 0; i < spins; ++i)
  {
    std::size_t const choice = roulette_wheel.select(prng, population);

    // Make a note of the fitness that was chosen
    auto fitness = static_cast<std::size_t>(population[choice].fitness());

    results[fitness] += 1;
  }

  for (auto const &[fitness, times_chosen] : results)
  {
    spdlog::info("Individual with fitness score {} chosen {} of 1000 times ({:.2f}%)", fitness, times_chosen, (static_cast<double>(times_chosen) / spins) * 100);
  }

  // Given the specified Population and their fitness scores, after 1000 spins of the wheel we expect the each Individual to have been selected the following number of times based on their fitness scores
  auto const expected = std::map<int, int>{{1, 104}, {2, 176}, {3, 294}, {4, 426}};

  // Check that the results matched what we expected
  REQUIRE(results == expected);
}


////////////////////////////////////////////////////////////////
TEST_CASE("Crossover", "[ga][crossover]")
{
  // Seed an mt19937 prng for a predictable "random" number to use for testing
  auto prng = std::mt19937{42};

  // Create a UniformCrossover CrossoverMethod
  auto uniform_crossover = ga::UniformCrossover{};

  // Create a pair of Chromosomes to use as parents
  auto parent_a = ga::Chromosome{{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0}};
  auto parent_b = ga::Chromosome{{-1.0, -2.0, -3.0, -4.0, -5.0, -6.0, -7.0, -8.0, -9.0, -10.0}};

  // Create a child by using the UniformCrossover method
  auto child = uniform_crossover.crossover(prng, parent_a, parent_b);

  // A UniformCrossover has an even 50/50 chance that a gene will come from either parent
  auto const expected = ga::Chromosome{{-1.0, 2.0, 3.0, -4.0, 5.0, 6.0, 7.0, 8.0, -9.0, -10.0}};

  // Check that the results matched what we expected
  REQUIRE(child == expected);
}

////////////////////////////////////////////////////////////////
TEST_CASE("Genetic Algorithm", "[ga][genetic_algorithm]")
{
  auto selection_method = std::make_unique<ga::RouletteWheelSelection>();
  auto crossover_method = std::make_unique<ga::UniformCrossover>();
  auto ga = ga::GeneticAlgorithm{std::move(selection_method), std::move(crossover_method)};

  REQUIRE(1 == 1);
}
