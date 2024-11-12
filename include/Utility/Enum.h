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

enum class ScreenAction
{
  GENERATE_EASY,
  GENERATE_MEDIUM,
  GENERATE_HARD,
  ENTER_CUSTOM,
  QUIT,
  COUNT
};

enum class HomeScreenOption
{
  GENERATE_EASY,
  GENERATE_MEDIUM,
  GENERATE_HARD,
  ENTER_CUSTOM,
  QUIT,
  COUNT
};
