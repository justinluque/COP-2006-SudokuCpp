#pragma once

#include <memory>
#include "SudokuPuzzle.h"
#include "ScreenManager.h"

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

  AppState currentState;
  AppScreen currentScreen;

  std::unique_ptr<ScreenManager> screenManager;

  int currentRow;
  int currentCol;
};
