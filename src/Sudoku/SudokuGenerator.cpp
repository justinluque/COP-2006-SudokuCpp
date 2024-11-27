#include "SudokuGenerator.h"

#include <vector>
#include <algorithm>

#include "SudokuSolver.h"
#include "Random.h"

std::unique_ptr<SudokuPuzzle> SudokuGenerator::generateEasy()
{
  return generate(Random::randint(36, 50));
}

std::unique_ptr<SudokuPuzzle> SudokuGenerator::generateMedium()
{
  return generate(Random::randint(32, 35));
}

std::unique_ptr<SudokuPuzzle> SudokuGenerator::generateHard()
{
  return generate(Random::randint(28, 31));
}

std::unique_ptr<SudokuPuzzle> SudokuGenerator::generateEmpty()
{
  return std::make_unique<SudokuPuzzle>();
}

std::unique_ptr<SudokuPuzzle> SudokuGenerator::generate(int clues)
{
  // Create an empty puzzle
  std::unique_ptr<SudokuPuzzle> puzzle = generateEmpty();

  // Use a backtracking approach to generate a valid solution first
  if (!randomlyFillPuzzle(puzzle, 0, 0))
  {
    return nullptr; // If unable to generate a valid solution, return nullptr
  }

  // Start removing numbers until the desired number of clues is reached
  int remainingClues = 81;

  // Keep track of removed cells
  std::vector<std::pair<int, int>> removedCells;

  // Remove numbers randomly until the number of clues is equal to the desired amount
  while (remainingClues > clues)
  {
    // Randomly pick a cell to remove
    int row = Random::randint(0, 8);
    int col = Random::randint(0, 8);

    // Skip already removed cells
    auto it = std::find(removedCells.begin(), removedCells.end(), std::make_pair(row, col));
    if (it != removedCells.end())
    {
      continue; // Skip if already removed
    }

    // Remove the number from the cell
    int removedValue = puzzle->getCellValue(row, col);
    puzzle->setCellValue(0, row, col);

    if (SudokuSolver::hasUniqueSolution(puzzle))
    {
      // If it still has a unique solution, keep the change
      removedCells.push_back({row, col});
      remainingClues--;
    }
    else
    {
      // If not, restore the value and try again
      puzzle->setCellValue(removedValue, row, col);
    }
  }

  return puzzle;
}

bool SudokuGenerator::randomlyFillPuzzle(std::unique_ptr<SudokuPuzzle> &puzzle, int row, int col)
{
  // If we've filled all rows, we're done
  if (row == 9)
  {
    return true;
  }

  // Move to the next row if we reach the end of the current one
  if (col == 9)
  {
    return randomlyFillPuzzle(puzzle, row + 1, 0);
  }

  // Try to fill the current cell with a random valid value
  std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  Random::shuffle(numbers); // Shuffle numbers to try them in random order

  for (int num : numbers)
  {
    if (SudokuSolver::isCorrectPlacement(puzzle, num, row, col)) // Check if the number is valid for this cell
    {
      puzzle->setCellValue(num, row, col);          // Place the number
      if (randomlyFillPuzzle(puzzle, row, col + 1)) // Recursively try to fill the rest of the puzzle
      {
        return true;
      }
      puzzle->setCellValue(0, row, col); // Undo the assignment if we couldn't proceed
    }
  }

  return false; // If no valid number can be placed, backtrack
}

void SudokuGenerator::setCluesToFixed(std::unique_ptr<SudokuPuzzle> &puzzle)
{
  for (int row = 0; row < 9; row++)
  {
    for (int col = 0; col < 9; col++)
    {
      if (puzzle->getCellValue(row, col) != 0)
        puzzle->setFixed(true, row, col);
    }
  }
}
