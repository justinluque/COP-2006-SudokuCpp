#include "Random.h"

#include <cstdlib>
#include <ctime>

namespace
{
  bool seeded = false;

  void seed()
  {
    if (!(seeded))
    {
      srand(std::time(nullptr));
      seeded = true;
    }
  }
}

int Random::randint(int min, int max)
{
  seed();

  return min + std::rand() % ((max + 1) - min);
}

int Random::choose(std::vector<int> things)
{
  seed();

  return things[Random::randint(0, things.size() - 1)];
}
