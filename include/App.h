#pragma once

#include <memory>
#include "SudokuPuzzle.h"

enum class AppState
{
  RUNNING,
  EXITING
};

enum class AppScreen
{
  HOME,  // SudokuCpp Title and a choice between an easy, medium, hard, or self-entered puzzle
  PUZZLE // Displays a puzzle, with all the shortcuts. Switch between cells using arrow keys
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

  AppState currentState;
  AppScreen currentScreen;

  std::unique_ptr<SudokuPuzzle> currentPuzzle;
  int currentRow;
  int currentCol;
};
