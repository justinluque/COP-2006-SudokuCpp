#pragma once

#include <memory>

#include <ncurses.h>

#include "SudokuPuzzle.h"
#include "Screen.h"
#include "Enum.h"

class PuzzleScreen : public Screen
{
public:
  PuzzleScreen(std::function<void(ScreenAction)> screenActionCallback, PuzzleDifficulty difficulty);
  ~PuzzleScreen() override;

  void refreshScreen() override;
  void handleInput() override;

private:
  int sizeY, sizeX;

  int gridStartY, gridStartX;
  int gridSizeY, gridSizeX;
  int cellSize;

  int helpStartY, helpStartX;
  int helpSizeY, helpSizeX;

  int currentCellY, currentCellX;

  bool messageDrawn;

  PuzzleDifficulty difficulty;

  WINDOW *window;
  WINDOW *subHelpWindow;

  std::unique_ptr<SudokuPuzzle> currentPuzzle;

  std::unique_ptr<SudokuPuzzle> solvedPuzzle;

  void solveCurrentPuzzle();

  void drawSudokuNums();

  void drawGrid();

  void drawNumByPos(int num, int row, int col);

  void drawHelp();

  void highlightOn();

  void highlightOff();

  void drawMessage(std::string msg);

  void clearMessage();
};
