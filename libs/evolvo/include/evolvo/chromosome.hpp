#pragma once

#include <iostream>
#include <vector>

#include "spdlog/fmt/ostr.h" // must be included for the operator<< overload to work with spdlog

namespace ga
{

class Chromosome : public std::vector<double>
{
public:
  friend std::ostream &operator<<(std::ostream &os, Chromosome const &rhs);
};


} // namespace ga