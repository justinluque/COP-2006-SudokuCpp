#pragma once

#include "Screen.h"

#include <ncurses/ncurses.h>

class PuzzleScreen : public Screen
{
public:
  PuzzleScreen();
  ~PuzzleScreen() override;

  void refresh() override;
  void handleInput() override;

private:
  WINDOW *window;
};
