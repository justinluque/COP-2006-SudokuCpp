#include <iostream>

#include <memory>

#include "SudokuPuzzle.h"
#include "SudokuSolver.h"

void display_puzzle(const std::unique_ptr<SudokuPuzzle> &puzzle)
{
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      std::cout << puzzle->getCellValue(i, j) << ' ';
    }
    std::cout << '\n';
  }
}

int main()
{

  std::unique_ptr<SudokuPuzzle> startingPuzzle = std::make_unique<SudokuPuzzle>(std::initializer_list<std::initializer_list<int>>{
      {0, 0, 0, 0, 0, 5, 1, 4, 7},
      {8, 0, 4, 9, 2, 0, 0, 0, 0},
      {0, 6, 0, 0, 0, 0, 0, 2, 9},
      {0, 0, 0, 0, 7, 0, 9, 0, 0},
      {0, 8, 2, 3, 0, 4, 7, 0, 0},
      {0, 1, 0, 0, 0, 8, 2, 0, 0},
      {0, 9, 5, 2, 0, 6, 4, 1, 8},
      {0, 0, 8, 4, 5, 9, 6, 7, 2},
      {0, 0, 0, 8, 1, 7, 3, 0, 5},
  });

  std::unique_ptr<SudokuPuzzle> solvedPuzzle = SudokuSolver::solveBacktracking(startingPuzzle);

  std::cout << "Starting Puzzle: \n";
  display_puzzle(startingPuzzle);

  std::cout << "\nSolved Puzzle: \n";
  display_puzzle(solvedPuzzle);

  return 0;
}
