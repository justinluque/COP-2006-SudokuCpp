#pragma once

#include <memory>
#include "Screen.h"

enum class AppScreen
{
  HOME,  // SudokuCpp Title and a choice between an easy, medium, hard, or self-entered puzzle
  PUZZLE // Displays a puzzle, with all the shortcuts. Switch between cells using arrow keys
};

enum class WindowType
{
  Home,
  Puzzle
};

class ScreenManager
{
public:
  ScreenManager();

  void refresh();
  void handleInput();

  void switchWindow(AppScreen screenType);

private:
  std::unique_ptr<Screen> currentScreen;
};
