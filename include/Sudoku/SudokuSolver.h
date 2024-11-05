#pragma once

#include <memory>
#include "SudokuPuzzle.h"

class SudokuSolver
{
public:
  SudokuSolver() = delete;

  static std::unique_ptr<SudokuPuzzle> solveBruteForce(const std::unique_ptr<SudokuPuzzle> &puzzle);

  static std::unique_ptr<SudokuPuzzle> solveBacktracking(const std::unique_ptr<SudokuPuzzle> &puzzle);

  // any other methods here if you find any
};