#pragma once

#include <memory>

#include <ncurses.h>

#include "SudokuPuzzle.h"
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
  int sizeY, sizeX;

  WINDOW *window;

  std::function<void(ScreenAction)> screenActionCallback;
  std::unique_ptr<SudokuPuzzle> currentPuzzle;

  void drawMainWindow();

  void drawConstantMainWindow();

  void highlightOn();

  void highlightOff();
};
