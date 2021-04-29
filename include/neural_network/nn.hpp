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
  explicit Network(std::vector<nn::Layer> const &layers);

  static auto random(std::mt19937 &prng, std::vector<nn::LayerTopology> const &layer_topologies) -> Network;

  auto propagate(std::vector<double> const &inputs) -> std::vector<double>;

  [[nodiscard]] auto layers() const -> std::vector<nn::Layer> const &;
  [[nodiscard]] auto weights() const -> std::vector<double>;
};

} // namespace nn
