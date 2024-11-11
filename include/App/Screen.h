#pragma once

#include <functional>

#include "Enum.h"

class Screen
{
public:
  Screen(std::function<void(AppScreen)> switchScreenCallback);
  virtual ~Screen() = default;

  virtual void refreshScreen() = 0;
  virtual void handleInput() = 0;

protected:
  std::function<void(AppScreen)> switchScreenCallback;
};
