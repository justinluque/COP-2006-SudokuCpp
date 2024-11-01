#include <iostream>
#include <memory>
#include <initializer_list>

#include "SudokuPuzzle.h"

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

// Justin Luque
// 10/30/24 8:36 PM
// these methods won't be used by the main app interface rather the SudokuGenerator but they should prove useful in creating test
// SudokuPuzzle objects  while I'm working on the puzzle generator
//
// I'd recommend just pulling up some online sudoku puzzle generator to find a single puzzle to test on (with a solution)
// the template grid i have i pulled from a website if you want to use that
//
// also, as it is right now zero inside the puzzle represents an unmarked cell
int main()
{
  std::unique_ptr<SudokuPuzzle> emptyPuzzle = std::make_unique<SudokuPuzzle>();

  display_puzzle(emptyPuzzle);

  std::cout << '\n';

  std::unique_ptr<SudokuPuzzle> templatePuzzle = std::make_unique<SudokuPuzzle>(std::initializer_list<std::initializer_list<int>>{
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

  display_puzzle(templatePuzzle);

  return 0;
}