#include "SudokoPuzzle.h"

#include <algorithm>

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
