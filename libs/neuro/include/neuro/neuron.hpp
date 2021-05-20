#pragma once

#include <vector>
#include <random>

namespace nn
{

class Neuron
{
private:
  double m_bias;
  std::vector<double> m_weights;

public:
  Neuron() = delete;

  // Construct a Neuron from a bias and a vector of weights
  explicit Neuron(double bias, std::vector<double> const &weights);

  // Create a random Neuron with the specified number outputs
  static auto random(std::mt19937 &prng, std::size_t outputs) -> Neuron;

  // Propogate the inputs through the neuron and return the result
  auto propagate(std::vector<double> const &inputs) -> double;

  // Getters
  [[nodiscard]] auto bias() const -> double;
  [[nodiscard]] auto weights() const -> std::vector<double> const &;
};

} // namespace nn
