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
  for (int colIterator = 0; colIterator < 9; colIterator++)
  {
    if (puzzle->getCellValue(row, colIterator) == num)
      return false;
  }

  for (int rowIterator = 0; rowIterator < 9; rowIterator++)
  {
    if (puzzle->getCellValue(rowIterator, col) == num)
      return false;
  }

  const int startRow = (row / 3) * 3;
  const int startCol = (col / 3) * 3;
  for (int rowIterator = startRow; rowIterator < startRow + 3; rowIterator++)
  {
    for (int columnIterator = startCol; columnIterator < startCol + 3; columnIterator++)
    {
      if (puzzle->getCellValue(rowIterator, columnIterator) == num)
        return false;
    }
  }

  return true;
}

bool SudokuSolver::hasUniqueSolution(const std::unique_ptr<SudokuPuzzle> &puzzle)
{
  if (!isValid(puzzle))
    return false; // For the puzzle to have solutions it must not break any rules of Sudoku

  int totalClues = 0;

  for (int row = 0; row < 9; row++)
  {
    for (int column = 0; column < 9; column++)
    {
      if (puzzle->getCellValue(row, column) != 0)
        totalClues++;
    }
  }

  // It is impossible to have a unique solution to a sudoku puzzle with less than 17 clues
  if (totalClues < 17)
    return false;

  std::unique_ptr<SudokuPuzzle> copiedPuzzle = std::make_unique<SudokuPuzzle>(*puzzle);

  bool secondSolutionFound = false;

  // If we can't find a second solution, there must be a unique solution to the puzzle
  return !findSecondSolution(copiedPuzzle, 0, 0, secondSolutionFound);
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

bool SudokuSolver::findSecondSolution(std::unique_ptr<SudokuPuzzle> &puzzle, int row, int col, bool &foundSolution)
{
  if (row == 9)
  {
    // We've found a complete solution
    if (foundSolution)
    {
      return true; // Second solution found
    }
    foundSolution = true; // First solution found
    return false;         // Continue searching for a second solution
  }

  if (col >= 9)
  {
    // Move to the next row
    return findSecondSolution(puzzle, row + 1, 0, foundSolution);
  }

  if (puzzle->getCellValue(row, col) > 0)
  {
    // Skip prefilled cells
    return findSecondSolution(puzzle, row, col + 1, foundSolution);
  }

  for (int digit = 1; digit <= 9; digit++)
  {
    if (isCorrectPlacement(puzzle, digit, row, col))
    {
      puzzle->setCellValue(digit, row, col);

      if (findSecondSolution(puzzle, row, col + 1, foundSolution))
      {
        return true; // If a second solution is found, propagate the success
      }

      // Backtrack
      puzzle->setCellValue(0, row, col);
    }
  }

  return false; // No second solution found
}
