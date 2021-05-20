#define CATCH_CONFIG_MAIN // This tells the Catch2 header to generate a main

#include "catch.hpp"

#include <random>
#include <vector>

#include <neuro/nn.hpp>


TEST_CASE("Neural Network", "[nn][network]")
{
  // Seed an mt19937 for a predictable "random" number to use for testing
  auto prng = std::mt19937{0};

  // Define our layer topologies
  auto layer_topologies = std::vector<nn::LayerTopology>{{3}, {5}, {1}};
  REQUIRE(layer_topologies.size() == 3);

  // Roll a new Network with randomly chosen Neuron values in each layer
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
  REQUIRE(outputs[0] == Approx(2.7889203667));
}


TEST_CASE("Neuron Random", "[nn][neuron][random]")
{
  // Seed an mt19937 for a predictable "random" number to use for testing
  auto prng = std::mt19937{0};

  // Roll a new random Neuron with 4 outputs
  auto neuron = nn::Neuron::random(prng, 4);

  // Check the bias of the neuron
  REQUIRE(neuron.bias() == Approx(0.185689233));

  // Check the number of weights for the neuron
  REQUIRE(neuron.weights().size() == 4);

  // Check the weights of the neuron
  REQUIRE_THAT(neuron.weights(), Catch::Matchers::Approx(std::vector<double>{0.6885314885, 0.71589124, 0.6945034748, 0.247127393}));
}


TEST_CASE("Neuron Propogation", "[nn][neuron][propagation]")
{
  // Create a new Neuron with the specified bias and weights
  auto neuron = nn::Neuron{0.1, {-0.3, 0.6, 0.9}};

  // Make up some fake input data and calculate the propogated value
  double output = neuron.propagate({0.5, -0.6, 0.7});

  // This is effectively the calculation the .propogate() function should be performing
  double expected = std::max(((0.1 + (0.5 * -0.3) + (-0.6 * 0.6) + (0.7 * 0.9))), 0.0);

  // Check the results of the propogation match what we expected
  REQUIRE(output == Approx(expected));
}


TEST_CASE("Neuron Output Restriction", "[nn][neuron][restriction]")
{
  // Create a new Neuron with the specified bias and weights
  auto neuron = nn::Neuron{0.0, {0.5}};

  // Calculate the propogated value given various different input values
  double v0 = neuron.propagate({-1.0}); // 0.0 + (-1.0 * 0.5) == -0.5 so this should produce 0.0
  double v1 = neuron.propagate({-0.5}); // 0.0 + (-0.5 * 0.5) == -0.25 so this should produce 0.0
  double v2 = neuron.propagate({0.0});  // 0.0 + (0.0 * 0.5) == 0.0 so this should produce 0.0
  double v3 = neuron.propagate({0.5});  // 0.0 + (0.5 * 0.5) == 0.25 so this should produce 0.25
  double v4 = neuron.propagate({1.0});  // 0.0 + (1.0 * 0.5) == 0.5 so this should produce 0.5

  // Check the results of the propogation match what we expected
  REQUIRE(v0 == Approx(0.0));
  REQUIRE(v1 == Approx(0.0));
  REQUIRE(v2 == Approx(0.0));
  REQUIRE(v3 == Approx(0.25));
  REQUIRE(v4 == Approx(0.5));

  // Create another new Neuron with a different bias and weights
  auto neuron2 = nn::Neuron{2.0, {0.15}};

  // Calculate the propogated value given various different input values
  double v5 = neuron2.propagate({-1.0}); // 2.0 + (-1.0 * 0.15) == 1.85 so this should produce 1.85
  double v6 = neuron2.propagate({-0.5}); // 2.0 + (-0.5 * 0.15) == 1.925 so this should produce 1.925
  double v7 = neuron2.propagate({0.0});  // 2.0 + (0.0 * 0.15) == 2.0 so this should produce 2.0
  double v8 = neuron2.propagate({0.5});  // 2.0 + (0.5 * 0.15) == 2.075 so this should produce 2.075
  double v9 = neuron2.propagate({-7.0}); // 2.0 + (-7.0 * 0.15) == 0.95 so this should produce 0.95

  // Check the results of the propogation match what we expected
  REQUIRE(v5 == Approx(1.85));
  REQUIRE(v6 == Approx(1.925));
  REQUIRE(v7 == Approx(2.0));
  REQUIRE(v8 == Approx(2.075));
  REQUIRE(v9 == Approx(0.95));
}
