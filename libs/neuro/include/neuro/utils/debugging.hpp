#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "neuro/layer_topology.hpp"

namespace utils
{

inline auto to_string(std::vector<nn::LayerTopology> const &input) -> std::string
{
  auto ss = std::stringstream{};

  ss << "[";

  for (std::size_t i = 0; i < input.size() - 1; ++i)
  {
    ss << input[i].m_neurons << ", ";
  }

  ss << input[input.size() - 1].m_neurons << "]";

  return ss.str();
}


inline auto to_string(std::vector<double> const &input) -> std::string
{
  auto ss = std::stringstream{};

  ss << "[";

  for (std::size_t i = 0; i < input.size() - 1; ++i)
  {
    ss << input[i] << ", ";
  }

  ss << input[input.size() - 1] << "]";

  return ss.str();
}

} // namespace utils
