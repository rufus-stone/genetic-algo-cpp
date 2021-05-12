#include <random>
#include <spdlog/spdlog.h>

#include <neuro/layer_topology.hpp>
#include <neuro/nn.hpp>
#include <neuro/utils/prng.hpp>
#include <neuro/utils/debugging.hpp>


int main()
{
  spdlog::info("Hello!");

  auto prng = std::mt19937{0};

  auto layer_topologies = std::vector<nn::LayerTopology>{{3}, {5}, {1}};
  spdlog::info("Layer topologies: {}", utils::to_string(layer_topologies));

  auto nn = nn::Network::random(prng, layer_topologies);

  std::vector<double> outputs = nn.propagate({1.0, -2.0, 3.5});
  spdlog::info("outputs: {}", utils::to_string(outputs));

  return EXIT_SUCCESS;
}
