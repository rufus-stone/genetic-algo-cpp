#include "neuro/nn.hpp"

#include <algorithm>
#include <numeric>

#include "neuro/layer.hpp"

namespace nn
{

// Construct a Network from a vector of Layers
Network::Network(std::vector<nn::Layer> const &layers) : m_layers(layers) {}

// Create a random Network from the specified Layer Topologies
auto Network::random(std::mt19937 &prng, std::vector<nn::LayerTopology> const &layer_topologies) -> Network
{
  return Network{Layer::random_layers_from_topologies(prng, layer_topologies)};
}

// Propogate the inputs through each Layer, and return the results
auto Network::propagate(std::vector<double> const &inputs) -> std::vector<double>
{
  // Take a copy of the input vector which we can then modify
  auto outputs = inputs;

  // For each layer in this->m_layers, set outputs to the result of calling layer.propogate(outputs)
  for (auto layer : this->m_layers)
  {
    outputs = layer.propagate(outputs);
  }

  return outputs;
}

auto Network::layers() const -> std::vector<nn::Layer> const &
{
  return this->m_layers;
}

auto Network::weights() const -> std::vector<double>
{
  auto output = std::vector<double>{};

  // self.layers.iter().flat_map(|layer| layer.neurons.iter()).flat_map(|neuron| once(neuron.bias).chain(neuron.weights.iter().cloned()))
  for (auto const &layer : this->m_layers)
  {
    for (auto const &neuron : layer.neurons())
    {
      output.push_back(neuron.bias());
      for (auto weight : neuron.weights())
      {
        output.push_back(weight);
      }
    }
  }

  return output;
}

} // namespace nn
