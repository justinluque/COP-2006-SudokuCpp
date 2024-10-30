#include "SudokoPuzzle.h"

#include <algorithm>

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
  return grid[row][col];
}

void SudokoPuzzle::setCellValue(int num, int row, int col)
{
  grid[row][col] = num;
}
