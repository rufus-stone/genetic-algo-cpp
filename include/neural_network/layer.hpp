#pragma once

#include <vector>

#include "neuron.hpp"
#include "layer_topology.hpp"

namespace nn
{

class Layer
{
private:
  std::vector<nn::Neuron> m_neurons;

public:
  Layer() = delete;
  explicit Layer(std::vector<nn::Neuron> const &neurons);

  static auto random(std::mt19937 &prng, std::size_t input_neurons, std::size_t output_neurons) -> Layer;

  auto propagate(std::vector<double> const &inputs) -> std::vector<double>;

  [[nodiscard]] auto neurons() const -> std::vector<nn::Neuron> const &;

  static auto random_layers_from_topologies(std::mt19937 &prng, std::vector<nn::LayerTopology> const &layer_topologies) -> std::vector<nn::Layer>;
};

} // namespace nn
