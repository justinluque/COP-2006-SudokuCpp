#include "SudokoGenerator.h"

std::unique_ptr<SudokoPuzzle> SudokoGenerator::generateEasy()
{
  std::unique_ptr<SudokoPuzzle> easyPuzzle = std::make_unique<SudokoPuzzle>();

  // TODO: fill the puzzle

  return easyPuzzle;
}

std::unique_ptr<SudokoPuzzle> SudokoGenerator::generateMedium()
{
  std::unique_ptr<SudokoPuzzle> mediumPuzzle = std::make_unique<SudokoPuzzle>();

  // TODO: fill the puzzle

  return mediumPuzzle;
}

std::unique_ptr<SudokoPuzzle> SudokoGenerator::generateHard()
{
  std::unique_ptr<SudokoPuzzle> hardPuzzle = std::make_unique<SudokoPuzzle>();

  // TODO: fill the puzzle

  return hardPuzzle;
}
