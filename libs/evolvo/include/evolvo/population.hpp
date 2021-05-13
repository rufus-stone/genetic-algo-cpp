#pragma once

#include <iostream>
#include <vector>

#include "evolvo/individual.hpp"

#include "spdlog/fmt/ostr.h" // must be included for the operator<< overload to work with spdlog

namespace ga
{

class Population : public std::vector<Individual>
{
public:
  [[nodiscard]] auto fitnesses() const -> std::vector<double>;

  friend std::ostream &operator<<(std::ostream &os, Chromosome const &rhs);
};


} // namespace ga