#pragma once

#include <ncurses/ncurses.h>

#include "Screen.h"
#include "Enum.h"

class PuzzleScreen : public Screen
{
public:
  PuzzleScreen(std::function<void(ScreenAction)> screenActionCallback);
  ~PuzzleScreen() override;

  void refreshScreen() override;
  void handleInput() override;

private:
  std::function<void(ScreenAction)> screenActionCallback;
  WINDOW *window;
};
