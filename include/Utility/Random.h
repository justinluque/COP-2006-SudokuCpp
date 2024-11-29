#pragma once

#include <vector>

namespace Random
{
  int randint(int min, int max);

  template <typename T>
  void shuffle(std::vector<T> &things);
}
