#include "neuro/layer.hpp"
#include "neuro/neuron.hpp"

#include <algorithm>
#include <iterator>
#include <numeric>

namespace nn
{

// Construct a Layer from a vector of Neurons
Layer::Layer(std::vector<nn::Neuron> const &neurons) : m_neurons(neurons) {}

// Create a random Layer with the specified number of input and output Neurons
auto Layer::random(std::mt19937 &prng, std::size_t input_neurons, std::size_t output_neurons) -> Layer
{
  auto neurons = std::vector<nn::Neuron>{};

  for (std::size_t i = 0; i < output_neurons; ++i)
  {
    neurons.emplace_back(nn::Neuron::random(prng, input_neurons));
  }

  return Layer{neurons};
}

// Propogate the inputs through each Neuron, and return the results
auto Layer::propagate(std::vector<double> const &inputs) -> std::vector<double>
{
  auto outputs = std::vector<double>{};

  // For each Neuron in this Layer, propogate the inputs and add the result to the vector of outputs
  for (auto &neuron : this->m_neurons)
  {
    outputs.emplace_back(neuron.propagate(inputs));
  }

  return outputs;
}

// Get a const ref to the vector of Neurons in this Layer
auto Layer::neurons() const -> std::vector<nn::Neuron> const &
{
  return this->m_neurons;
}

// Build a set of random Layers from the specified Layer Topologies
auto Layer::random_layers_from_topologies(std::mt19937 &prng, std::vector<nn::LayerTopology> const &layer_topologies) -> std::vector<nn::Layer>
{
  auto built_layers = std::vector<nn::Layer>{};

  for (std::size_t i = 0; i < layer_topologies.size() - 1; ++i)
  {
    auto const &lhs = layer_topologies[i];
    auto const &rhs = layer_topologies[i + 1];

    built_layers.emplace_back(nn::Layer::random(prng, lhs.m_neurons, rhs.m_neurons));
  }

  return built_layers;
}

} // namespace nn
