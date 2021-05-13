#include "evolvo/chromosome.hpp"

#include "evolvo/utils/debugging.hpp"

namespace ga
{

std::ostream &operator<<(std::ostream &os, Chromosome const &rhs)
{
  os << utils::to_string(rhs);
  return os;
}

} // namespace ga