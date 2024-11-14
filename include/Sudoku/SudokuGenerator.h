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
};
