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
  int gridStartY, gridStartX;
  int cellSize;

  WINDOW *window;

  std::function<void(ScreenAction)> screenActionCallback;
  std::unique_ptr<SudokuPuzzle> currentPuzzle;

  void drawMainWindow();

  void drawGrid();

  void drawNumByPos(int num, int row, int col);

  void highlightOn();

  void highlightOff();
};
