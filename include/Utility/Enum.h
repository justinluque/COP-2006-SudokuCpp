#pragma once

enum class AppScreen
{
  HOME,  // SudokuCpp Title and a choice between an easy, medium, hard, or self-entered puzzle
  PUZZLE // Displays a puzzle, with all the shortcuts. Switch between cells using arrow keys
};

enum class AppState
{
  RUNNING,
  EXITING
};
