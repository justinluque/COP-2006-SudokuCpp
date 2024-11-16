#include "SudokuSolver.h"

#include <memory>

std::unique_ptr<SudokuPuzzle> SudokuSolver::solveBacktracking(const std::unique_ptr<SudokuPuzzle> &puzzle)
{
  std::unique_ptr<SudokuPuzzle> solvedPuzzle = std::make_unique<SudokuPuzzle>(*puzzle);

  if (recursiveAlgorithm(solvedPuzzle, 0, 0))
  {
    return solvedPuzzle;
  }

  return nullptr;
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

      if (rows[row][value - 1]++ || columns[value - 1][col]++ || subgrids[row / 3][col / 3][value - 1]++)
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

bool SudokuSolver::isCorrectPlacement(const std::unique_ptr<SudokuPuzzle> &puzzle, int num, int row, int col)
{
  std::unique_ptr<SudokuPuzzle> tempPuzzle = std::make_unique<SudokuPuzzle>(*puzzle);

  tempPuzzle->setCellValue(num, row, col);

  return isValid(tempPuzzle);
}

bool SudokuSolver::recursiveAlgorithm(std::unique_ptr<SudokuPuzzle> &puzzle, int row, int col)
{
  if (row == 9)
  {
    return true;
  }

  if (col >= 9)
  {
    return recursiveAlgorithm(puzzle, row + 1, 0);
  }

  if (puzzle->getCellValue(row, col) > 0)
  {
    return recursiveAlgorithm(puzzle, row, col + 1);
  }

  for (int digit = 1; digit <= 9; digit++)
  {
    if (isCorrectPlacement(puzzle, digit, row, col))
    {
      puzzle->setCellValue(digit, row, col);
      if (recursiveAlgorithm(puzzle, row, col + 1))
      {
        return true;
      }
    }
    puzzle->setCellValue(0, row, col);
  }
  return false;
}
