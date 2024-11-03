#pragma once

#include "ncurses/ncurses.h"

class Window
{
public:
  Window();
  ~Window();

  virtual void refresh();
  virtual void handleInput();

private:
  WINDOW *window;
};
