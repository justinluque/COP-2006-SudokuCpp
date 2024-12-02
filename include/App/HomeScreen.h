#pragma once

#include <ncurses.h>

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

  WINDOW *window;

  void drawOptions();

  void drawMainWindow();

  void drawResizePrompt();

  void highlightOn();

  void highlightOff();

  bool windowIsOutOfBounds();
};
