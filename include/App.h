#pragma once

#include <memory>
#include "SudokuPuzzle.h"

enum class AppState
{
  RUNNING,
  EXITING
};

class App
{
public:
  App();
  ~App();

  void run();

private:
  void initializeCurses();
  void destroyCurses();
  void displayPuzzle();
  void handleInput();
  void generatePuzzle(); // CTRL_N
  void checkPuzzle();    // CTRL_C
  void solvePuzzle();    // CTRL_S
  void giveHint();       // CTRL_H
  void quit();           // CTRL_Q

  AppState appState;
  std::unique_ptr<SudokuPuzzle> currentPuzzle;
  int currentRow;
  int currentCol;
};
