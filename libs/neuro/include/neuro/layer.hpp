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

  // Construct a Layer from a vector of Neurons
  explicit Layer(std::vector<nn::Neuron> const &neurons);

  // Create a random Layer with the specified number of input and output neurons
  static auto random(std::mt19937 &prng, std::size_t input_neurons, std::size_t output_neurons) -> Layer;

  // Propogate the inputs through each Neuron, and return the results
  auto propagate(std::vector<double> const &inputs) -> std::vector<double>;

  // Get a const ref to the vector of Neurons in this Layer
  [[nodiscard]] auto neurons() const -> std::vector<nn::Neuron> const &;

  // Build a set of random Layers from the specified Layer Topologies
  static auto random_layers_from_topologies(std::mt19937 &prng, std::vector<nn::LayerTopology> const &layer_topologies) -> std::vector<nn::Layer>;
};

} // namespace nn
