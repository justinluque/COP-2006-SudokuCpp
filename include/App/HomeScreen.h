#pragma once

#include "Screen.h"

#include <ncurses/ncurses.h>

class HomeScreen : public Screen
{
public:
  HomeScreen();
  ~HomeScreen() override;

  void refresh() override;
  void handleInput() override;

private:
  WINDOW *window;
};
