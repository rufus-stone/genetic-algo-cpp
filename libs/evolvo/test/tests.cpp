#include "evolvo/chromosome.hpp"
#include "evolvo/individual.hpp"
#define CATCH_CONFIG_MAIN // This tells the Catch2 header to generate a main

#include "catch.hpp"

#include <random>
#include <vector>

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
  auto const chromo = ga::Chromosome{{1.1, 2.0, -3.3, 4.6}};
  auto const indiv = ga::Individual{chromo};

  REQUIRE(indiv.chromosome() == chromo);
  REQUIRE_THAT(indiv.chromosome(), Catch::Matchers::Approx(std::vector<double>{1.1, 2.0, -3.3, 4.6}));
  REQUIRE(indiv.fitness() == 0.0);
}
