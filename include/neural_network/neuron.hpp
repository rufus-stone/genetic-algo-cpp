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
  explicit Neuron(double bias, std::vector<double> const &weights);

  static auto random(std::mt19937 &prng, std::size_t outputs) -> Neuron;

  auto propagate(std::vector<double> const &inputs) -> double;

  [[nodiscard]] auto bias() const -> double;
  [[nodiscard]] auto weights() const -> std::vector<double> const &;
};

} // namespace nn
