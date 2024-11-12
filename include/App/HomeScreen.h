#pragma once

#include <ncurses/ncurses.h>

#include "Screen.h"
#include "Enum.h"

class HomeScreen : public Screen
{
public:
  HomeScreen(std::function<void(ScreenAction)> screenActionCallback);
  ~HomeScreen() override;

  void refreshScreen() override;
  void handleInput() override;

private:
  int sizeY, sizeX;
  HomeScreenOption selectedOption;
  std::function<void(ScreenAction)> screenActionCallback;
  WINDOW *window;

  void drawMainWindow();

  void drawConstantMainWindow();

  void drawResizePrompt();

  void highlightOn();

  void highlightOff();

  bool windowIsOutOfBounds();
};
