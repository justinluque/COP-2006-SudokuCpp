#pragma once

#include <functional>

#include "Enum.h"

class Screen
{
public:
  Screen(std::function<void(ScreenAction)> screenActionCallback);
  virtual ~Screen() = default;

  virtual void refreshScreen() = 0;
  virtual void handleInput() = 0;

protected:
  std::function<void(ScreenAction)> screenActionCallback;
};
