#pragma once

#include <memory>
#include "SudokuPuzzle.h"
#include "ScreenManager.h"

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

  AppState currentState;

  std::shared_ptr<ScreenManager> screenManager;

  int currentRow;
  int currentCol;
};
