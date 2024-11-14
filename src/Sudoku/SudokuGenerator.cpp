#include "SudokuGenerator.h"

#include <vector>

#include "SudokuSolver.h"
#include "Random.h"

std::unique_ptr<SudokuPuzzle> SudokuGenerator::generateEasy()
{
  std::unique_ptr<SudokuPuzzle> easyPuzzle = std::make_unique<SudokuPuzzle>();

  std::vector<int> startingNums = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  for (int i = 0; i < 9; i++)
  {
    int choice = Random::randint(0, startingNums.size() - 1);
    easyPuzzle->setCellValue(startingNums[i], 0, i);
    startingNums.erase(startingNums.begin() + choice);
  }

  easyPuzzle = SudokuSolver::solveBacktracking(easyPuzzle);

  for (int i = 0; i < 5; i++)
  {
    int randomRow = Random::randint(0, 8);
    int randomCol = Random::randint(0, 8);

    if (easyPuzzle->getCellValue(randomRow, randomCol) != 0)
      easyPuzzle->strongSetValue(0, randomRow, randomCol);
    else
      i--;
  }

  for (int row = 0; row < 9; row++)
  {
    for (int col = 0; col < 9; col++)
    {
      if (easyPuzzle->getCellValue(row, col) == 0)
      {
        easyPuzzle->setFixed(true, row, col);
      }
    }
  }

  return easyPuzzle;
}

std::unique_ptr<SudokuPuzzle> SudokuGenerator::generateMedium()
{
  std::unique_ptr<SudokuPuzzle> mediumPuzzle = std::make_unique<SudokuPuzzle>();

  std::vector<int> startingNums = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  for (int i = 0; i < 9; i++)
  {
    int choice = Random::randint(0, startingNums.size() - 1);
    mediumPuzzle->setCellValue(startingNums[i], 0, i);
    startingNums.erase(startingNums.begin() + choice);
  }

  mediumPuzzle = SudokuSolver::solveBacktracking(mediumPuzzle);

  for (int i = 0; i < 9; i++)
  {
    int randomRow = Random::randint(0, 8);
    int randomCol = Random::randint(0, 8);

    if (mediumPuzzle->getCellValue(randomRow, randomCol) != 0)
      mediumPuzzle->strongSetValue(0, randomRow, randomCol);
    else
      i--;
  }

  for (int row = 0; row < 9; row++)
  {
    for (int col = 0; col < 9; col++)
    {
      if (mediumPuzzle->getCellValue(row, col) == 0)
      {
        mediumPuzzle->setFixed(true, row, col);
      }
    }
  }

  return mediumPuzzle;
}

std::unique_ptr<SudokuPuzzle> SudokuGenerator::generateHard()
{
  std::unique_ptr<SudokuPuzzle> hardPuzzle = std::make_unique<SudokuPuzzle>();

  std::vector<int> startingNums = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  for (int i = 0; i < 11; i++)
  {
    int choice = Random::randint(0, startingNums.size() - 1);
    hardPuzzle->setCellValue(startingNums[i], 0, i);
    startingNums.erase(startingNums.begin() + choice);
  }

  hardPuzzle = SudokuSolver::solveBacktracking(hardPuzzle);

  for (int i = 0; i < 9; i++)
  {
    int randomRow = Random::randint(0, 8);
    int randomCol = Random::randint(0, 8);

    if (hardPuzzle->getCellValue(randomRow, randomCol) != 0)
      hardPuzzle->strongSetValue(0, randomRow, randomCol);
    else
      i--;
  }

  for (int row = 0; row < 9; row++)
  {
    for (int col = 0; col < 9; col++)
    {
      if (hardPuzzle->getCellValue(row, col) == 0)
      {
        hardPuzzle->setFixed(true, row, col);
      }
    }
  }

  return hardPuzzle;
}

std::unique_ptr<SudokuPuzzle> SudokuGenerator::generateEmpty()
{
  return std::make_unique<SudokuPuzzle>();
}
