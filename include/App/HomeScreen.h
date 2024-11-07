#pragma once

#include "Screen.h"
#include "Enum.h"

#include <ncurses/ncurses.h>

class HomeScreen : public Screen
{
public:
  HomeScreen(std::function<void(AppScreen)> switchScreenCallback);
  ~HomeScreen() override;

  void refresh() override;
  void handleInput() override;

private:
  std::function<void(AppScreen)> switchScreenCallback;
  WINDOW *window;
};
