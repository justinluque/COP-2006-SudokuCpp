#pragma once

#include "ncurses/ncurses.h"

class Screen
{
public:
  Screen();
  ~Screen();

  virtual void refresh();
  virtual void handleInput();

private:
  WINDOW *window;
};
