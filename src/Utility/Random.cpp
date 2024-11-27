#include "Random.h"

#include <random>
#include <algorithm>
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

void Random::shuffle(std::vector<int> &things)
{
  seed();

  std::shuffle(things.begin(), things.end(), rng);
}
