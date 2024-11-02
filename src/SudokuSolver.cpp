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
