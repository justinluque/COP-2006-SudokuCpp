#pragma once

#include <memory>

#include "SudokuPuzzle.h"

class SudokuGenerator
{
public:
  SudokuGenerator() = delete;

  static std::unique_ptr<SudokuPuzzle> generateEasy();

  static std::unique_ptr<SudokuPuzzle> generateMedium();

  static std::unique_ptr<SudokuPuzzle> generateHard();

  static std::unique_ptr<SudokuPuzzle> generateEmpty();

private:
  static std::unique_ptr<SudokuPuzzle> generate(int clues);

  static bool randomlyFillPuzzle(std::unique_ptr<SudokuPuzzle> &puzzle, int row, int col);

  static void setCluesToFixed(std::unique_ptr<SudokuPuzzle> &puzzle);
};
