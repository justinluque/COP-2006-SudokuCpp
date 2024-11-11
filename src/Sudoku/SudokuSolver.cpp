#include "SudokuSolver.h"

#include <memory>

std::unique_ptr<SudokuPuzzle> SudokuSolver::solveBacktracking(const std::unique_ptr<SudokuPuzzle> &puzzle)
{
  std::unique_ptr<SudokuPuzzle> solvedPuzzle = std::make_unique<SudokuPuzzle>(*puzzle);

  // TODO: stuff here

  return solvedPuzzle;
}

std::unique_ptr<SudokuPuzzle> SudokuSolver::solveBruteForce(const std::unique_ptr<SudokuPuzzle> &puzzle)
{
  std::unique_ptr<SudokuPuzzle> solvedPuzzle = std::make_unique<SudokuPuzzle>(*puzzle);

  // TODO: stuff here

  return solvedPuzzle;
}

// Really cool solution inspired by neetcode (https://www.youtube.com/watch?v=TjFXEUCMqI8)
bool SudokuSolver::isValid(const std::unique_ptr<SudokuPuzzle> &puzzle)
{
  // "hashmaps" to track number of occurences of nums 1-9
  int rows[9][9] = {0};
  int columns[9][9] = {0};
  int subgrids[3][3][9] = {0};

  for (int row = 0; row < 9; row++)
  {
    for (int col = 0; col < 9; col++)
    {
      int value = puzzle->getCellValue(row, col);

      if (value == 0)
        continue;

      if (rows[row][value]++ || columns[value][col]++ || subgrids[row / 3][col / 3][value]++)
        return false;
    }
  }

  return true;
}

bool SudokuSolver::isFull(const std::unique_ptr<SudokuPuzzle> &puzzle)
{
  for (int row = 0; row < 9; row++)
  {
    for (int col = 0; col < 9; col++)
    {
      if (puzzle->getCellValue(row, col) == 0)
        return false;
    }
  }
  return true;
}

bool SudokuSolver::isSolved(const std::unique_ptr<SudokuPuzzle> &puzzle)
{
  return isValid(puzzle) && isFull(puzzle);
}
