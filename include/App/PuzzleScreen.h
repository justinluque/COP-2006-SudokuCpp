#pragma once

#include "Screen.h"
#include "Enum.h"

#include <ncurses/ncurses.h>

class PuzzleScreen : public Screen
{
public:
  PuzzleScreen(std::function<void(AppScreen)> switchScreenCallback);
  ~PuzzleScreen() override;

  void refresh() override;
  void handleInput() override;

private:
  std::function<void(AppScreen)> switchScreenCallback;
  WINDOW *window;
};
