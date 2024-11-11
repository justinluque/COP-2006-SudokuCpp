#pragma once

#include <ncurses/ncurses.h>

#include "Screen.h"
#include "Enum.h"

class PuzzleScreen : public Screen
{
public:
  PuzzleScreen(std::function<void(AppScreen)> switchScreenCallback);
  ~PuzzleScreen() override;

  void refreshScreen() override;
  void handleInput() override;

private:
  std::function<void(AppScreen)> switchScreenCallback;
  WINDOW *window;
};
