#pragma once

#include "Screen.h"

#include <ncurses/ncurses.h>

class PuzzleScreen : public Screen
{
public:
  PuzzleScreen(const std::shared_ptr<ScreenManager> &screenManager);
  ~PuzzleScreen() override;

  void refresh() override;
  void handleInput() override;

private:
  std::shared_ptr<ScreenManager> screenManager;
  WINDOW *window;
};
