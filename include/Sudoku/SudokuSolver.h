#pragma once

#include <memory>

#include "SudokuPuzzle.h"

class SudokuSolver
{
public:
  SudokuSolver() = delete;

  static std::unique_ptr<SudokuPuzzle> solveBruteForce(const std::unique_ptr<SudokuPuzzle> &puzzle);

  static std::unique_ptr<SudokuPuzzle> solveBacktracking(const std::unique_ptr<SudokuPuzzle> &puzzle);

  static bool isValid(const std::unique_ptr<SudokuPuzzle> &puzzle);

  static bool isFull(const std::unique_ptr<SudokuPuzzle> &puzzle);

  static bool isSolved(const std::unique_ptr<SudokuPuzzle> &puzzle);

private:
  static bool isCorrectPlacement(const std::unique_ptr<SudokuPuzzle> &puzzle, int num, int row, int col);

  static bool recursiveAlgorithm(std::unique_ptr<SudokuPuzzle> &puzzle, int row, int col);
};
