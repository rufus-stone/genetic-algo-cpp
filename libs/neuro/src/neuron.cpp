#include "neuro/neuron.hpp"

#include <algorithm>
#include <numeric>

#include "neuro/utils/exceptions.hpp"


namespace nn
{

// Construct a Neuron from a bias and a vector of weights
Neuron::Neuron(double bias, std::vector<double> const &weights) : m_bias(bias), m_weights(weights) {}

// Create a random Neuron with the specified number outputs
auto Neuron::random(std::mt19937 &prng, std::size_t outputs) -> Neuron
{
  // Generate a random bias (between -1 and 1 inclusive)
  auto dist = std::uniform_real_distribution<double>(-1, 1);
  double bias = dist(prng);

  // Generate random weights (between -1 and 1 inclusive)
  auto weights = std::vector<double>{};

  for (std::size_t i = 0; i < outputs; ++i)
  {
    weights.push_back(dist(prng));
  }

  return Neuron{bias, weights};
}

// Propogate the inputs through the neuron and return the result
auto Neuron::propagate(std::vector<double> const &inputs) -> double
{
  // There should always be an equal number of inputs and weights (as the weights modify each input)
  if (inputs.size() != this->m_weights.size())
  {
    throw nn::xcpt::invalid_parameter("The number of inputs should equal the number of weights!");
  }

  // Take each input, multiply it by the corresponding weight, and sum all the results together
  // let output = inputs.iter().zip(&self.weights).map(| (input, weight) | input * weight).sum::<f32>();
  auto multiplied = std::vector<double>{};
  std::transform(std::begin(inputs), std::end(inputs), std::begin(this->m_weights), std::back_inserter(multiplied), std::multiplies{});
  double output = std::accumulate(std::begin(multiplied), std::end(multiplied), 0.0);

  return output;
}


auto Neuron::bias() const -> double
{
  return this->m_bias;
}

auto Neuron::weights() const -> std::vector<double> const &
{
  return this->m_weights;
}


} // namespace nn
  //