#include "SudokuGenerator.h"

std::unique_ptr<SudokuPuzzle> SudokuGenerator::generateEasy()
{
  std::unique_ptr<SudokuPuzzle> easyPuzzle = std::make_unique<SudokuPuzzle>();

  // TODO: fill the puzzle

  return easyPuzzle;
}

std::unique_ptr<SudokuPuzzle> SudokuGenerator::generateMedium()
{
  std::unique_ptr<SudokuPuzzle> mediumPuzzle = std::make_unique<SudokuPuzzle>();

  // TODO: fill the puzzle

  return mediumPuzzle;
}

std::unique_ptr<SudokuPuzzle> SudokuGenerator::generateHard()
{
  std::unique_ptr<SudokuPuzzle> hardPuzzle = std::make_unique<SudokuPuzzle>();

  // TODO: fill the puzzle

  return hardPuzzle;
}
