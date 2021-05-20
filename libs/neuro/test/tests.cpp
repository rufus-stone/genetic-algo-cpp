#define CATCH_CONFIG_MAIN // This tells the Catch2 header to generate a main

#include "catch.hpp"

#include <random>
#include <vector>

#include <neuro/nn.hpp>

////////////////////////////////////////////////////////////////
TEST_CASE("Neural Network", "[nn]")
{
  auto layer_topologies = std::vector<nn::LayerTopology>{{3}, {5}, {1}};
  REQUIRE(layer_topologies.size() == 3);

  auto prng = std::mt19937{0};
  auto nn = nn::Network::random(prng, layer_topologies);

  // Check the weights of the entire network
  REQUIRE_THAT(nn.weights(), Catch::Matchers::Approx(std::vector<double>{0.185689233, 0.6885314885, 0.71589124, 0.6945034748, 0.247127393, -0.2312365833, -0.4049307893, -0.8865740481, -0.4546874105, -0.0446697765, 0.6243374533, -0.0400456569, -0.2144304134, 0.6721575381, -0.3252076767, 0.2963437532, -0.2635169253, 0.914310309, -0.7192984448, 0.7401745025, -0.0527839195, 0.6018215054, 0.0409549612, 0.3577590677, 0.4412653032, 0.1640395828}));

  // Check the bias of the first neuron in the first layer
  REQUIRE(nn.layers().front().neurons().front().bias() == Approx(0.185689233));

  // Check the weights of the second neuron in the first layer
  REQUIRE_THAT(nn.layers().front().neurons()[1].weights(), Catch::Matchers::Approx(std::vector<double>{-0.2312365833, -0.4049307893, -0.8865740481}));

  // Propogate with the specified inputs
  std::vector<double> outputs = nn.propagate({1.0, -2.0, 3.5});

  // Check that we only get one output
  REQUIRE(outputs.size() == 1);

  // Check the value of the output
  REQUIRE(outputs[0] == Approx(2.2515651374));
}