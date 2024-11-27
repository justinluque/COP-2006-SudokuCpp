#pragma once

#include <vector>

namespace Random
{
  int randint(int min, int max);

  void shuffle(std::vector<int> &things);
}
