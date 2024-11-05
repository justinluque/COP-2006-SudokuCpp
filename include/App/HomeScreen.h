#pragma once

#include "Screen.h"

#include <ncurses/ncurses.h>

class HomeScreen : public Screen
{
public:
  HomeScreen(std::shared_ptr<ScreenManager> screenManager);
  ~HomeScreen() override;

  void refresh() override;
  void handleInput() override;

private:
  std::shared_ptr<ScreenManager> screenManager;
  WINDOW *window;
};
