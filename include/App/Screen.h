#pragma once

#include <memory>

class ScreenManager;

class Screen
{
public:
  Screen(std::shared_ptr<ScreenManager> screenManager);
  virtual ~Screen() = default;

  virtual void refresh() = 0;
  virtual void handleInput() = 0;

protected:
  std::shared_ptr<ScreenManager> screenManager;
};
