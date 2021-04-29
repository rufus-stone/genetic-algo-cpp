#include "neural_network/layer.hpp"
#include "neural_network/neuron.hpp"

#include <algorithm>
#include <iterator>
#include <numeric>

#include <spdlog/spdlog.h>


namespace nn
{

Layer::Layer(std::vector<nn::Neuron> const &neurons) : m_neurons(neurons)
{
}

auto Layer::random(std::mt19937 &prng, std::size_t input_neurons, std::size_t output_neurons) -> Layer
{
  auto neurons = std::vector<nn::Neuron>{};

  for (std::size_t i = 0; i < output_neurons; ++i)
  {
    neurons.emplace_back(nn::Neuron::random(prng, input_neurons));
  }

  return Layer{neurons};
}

auto Layer::propagate(std::vector<double> const &inputs) -> std::vector<double>
{
  auto outputs = std::vector<double>{};

  // For each neuron in this layer, propogate the inputs and add the result to the vector of outputs
  for (auto &neuron : this->m_neurons)
  {
    outputs.emplace_back(neuron.propagate(inputs));
  }

  return outputs;
}

auto Layer::neurons() const -> std::vector<nn::Neuron> const &
{
  return this->m_neurons;
}


auto Layer::random_layers_from_topologies(std::mt19937 &prng, std::vector<nn::LayerTopology> const &layer_topologies) -> std::vector<nn::Layer>
{
  // let built_layers = layers.windows(2).map(|layers| Layer::random(prng, layers[0].neurons, layers[1].neurons)).collect::<Vec<Layer>>();
  auto built_layers = std::vector<nn::Layer>{};

  for (std::size_t i = 0; i < layer_topologies.size() - 1; ++i)
  {
    auto const &lhs = layer_topologies[i];
    auto const &rhs = layer_topologies[i + 1];

    spdlog::info("lhs: {}", lhs.m_neurons);
    spdlog::info("rhs: {}", rhs.m_neurons);

    built_layers.emplace_back(nn::Layer::random(prng, lhs.m_neurons, rhs.m_neurons));
  }

  return built_layers;
}

} // namespace nn
