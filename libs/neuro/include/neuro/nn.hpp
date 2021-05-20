#pragma once

#include <vector>
#include <random>

#include "layer.hpp"
#include "layer_topology.hpp"

namespace nn
{

class Network
{
private:
  std::vector<nn::Layer> m_layers;

public:
  Network() = delete;

  // Construct a Network from a vector of Layers
  explicit Network(std::vector<nn::Layer> const &layers);

  // Create a random Network from the specified Layer Topologies
  static auto random(std::mt19937 &prng, std::vector<nn::LayerTopology> const &layer_topologies) -> Network;

  // Propogate the inputs through each Layer, and return the results
  auto propagate(std::vector<double> const &inputs) -> std::vector<double>;

  // Getters
  [[nodiscard]] auto layers() const -> std::vector<nn::Layer> const &;
  [[nodiscard]] auto weights() const -> std::vector<double>; //
};

} // namespace nn
