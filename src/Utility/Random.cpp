#include "Random.h"

#include <random>
#include <algorithm>
#include <stdexcept>
#include <utility>
#include <ctime>

namespace
{
  std::mt19937 rng; // Mersenne Twister engine
  bool seeded = false;

  void seed()
  {
    if (!seeded)
    {
      rng.seed(std::time(nullptr)); // Seed with the current time
      seeded = true;
    }
  }
}

int Random::randint(int min, int max)
{
  seed();

  std::uniform_int_distribution<int> distribution(min, max);
  return distribution(rng);
}

template <typename T>
T Random::choose(std::vector<T> &things)
{
  if (things.empty())
    throw std::invalid_argument("Cannot choose from an empty vector.");

  seed();

  std::uniform_int_distribution<std::size_t> distribution(0, things.size() - 1);

  return things[distribution(rng)];
}

template <typename T>
void Random::shuffle(std::vector<T> &things)
{
  seed();

  std::shuffle(things.begin(), things.end(), rng);
}

// Explicitly instantiate templates
template void Random::shuffle(std::vector<int> &things);
template std::pair<int, int> Random::choose(std::vector<std::pair<int, int>> &things);
