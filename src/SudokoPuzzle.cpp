#include "SudokoPuzzle.h"

#include <algorithm>
#include <stdexcept>

// Default constructor
SudokoPuzzle::SudokoPuzzle()
{
  SudokoPuzzle::reset();
}

// Created for debugging purposes and is only intended to be used for such
SudokoPuzzle::SudokoPuzzle(const int (&grid)[9][9])
{
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      this->grid[i][j] = grid[i][j];
    }
  }
}

void SudokoPuzzle::reset()
{
  std::fill(&grid[0][0], &grid[0][0] + 9 * 9, 0);
}

int SudokoPuzzle::getCellValue(int row, int col) const
{
  if (row > 9 || row < 1 || col > 9 || col < 1)
    throw std::out_of_range("Row or column index is out of range");

  return grid[row - 1][col - 1];
}

void SudokoPuzzle::setCellValue(int num, int row, int col)
{
  if (row > 9 || row < 1 || col > 9 || col < 1)
    throw std::out_of_range("Row or column index is out of range");

  grid[row - 1][col - 1] = num;
}
