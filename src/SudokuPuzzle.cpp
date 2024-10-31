#include "SudokuPuzzle.h"

#include <algorithm>
#include <stdexcept>

// Default constructor
SudokuPuzzle::SudokuPuzzle()
{
  SudokuPuzzle::reset();
}

// Created for debugging purposes and is only intended to be used for such
SudokuPuzzle::SudokuPuzzle(std::initializer_list<std::initializer_list<int>> grid)
{
  int row_index = 1, col_index = 1;
  for (const auto &row : grid)
  {
    if (row_index > 9)
      throw std::out_of_range("Too many rows to construct 9x9 grid");
    for (const int &num : row)
    {
      if (col_index > 9)
        throw std::out_of_range("Too many columns to construct 9x9 grid");
      this->setCellValue(num, row_index, col_index);
      col_index++;
    }
    if (col_index < 9)
      throw std::out_of_range("Too few columns to construct 9x9 grid");
    col_index = 1;
    row_index++;
  }
  if (row_index < 9)
    throw std::out_of_range("Too few rows to construct 9x9 grid");
}

void SudokuPuzzle::reset()
{
  std::fill(&grid[0][0], &grid[0][0] + 9 * 9, 0);
}

int SudokuPuzzle::getCellValue(int row, int col) const
{
  if (row > 9 || row < 1 || col > 9 || col < 1)
    throw std::out_of_range("Row or column index is out of range");

  return grid[row - 1][col - 1];
}

void SudokuPuzzle::setCellValue(int num, int row, int col)
{
  if (row > 9 || row < 1 || col > 9 || col < 1)
    throw std::out_of_range("Row or column index is out of range");

  grid[row - 1][col - 1] = num;
}
