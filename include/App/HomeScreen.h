#pragma once

#include <ncurses/ncurses.h>

#include "Screen.h"
#include "Enum.h"

class HomeScreen : public Screen
{
public:
  HomeScreen(std::function<void(AppScreen)> switchScreenCallback);
  ~HomeScreen() override;

  void refresh() override;
  void handleInput() override;

private:
  int sizeY, sizeX;
  std::function<void(AppScreen)> switchScreenCallback;
  WINDOW *window;

  void drawMainWindow();

  void drawResizePrompt();

  bool windowIsOutOfBounds();
};
