#include "SudokuPuzzle.h"

#include <algorithm>
#include <stdexcept>
#include <string>

// Default constructor
SudokuPuzzle::SudokuPuzzle()
{
  SudokuPuzzle::reset();
}

// Created for debugging purposes and is only intended to be used for such
SudokuPuzzle::SudokuPuzzle(std::initializer_list<std::initializer_list<int>> grid)
{
  int row_index = 0, col_index = 0;
  for (const auto &row : grid)
  {
    if (row_index > 8)
      throw std::out_of_range("Too many rows to construct 9x9 grid");
    for (const int &num : row)
    {
      if (col_index > 8)
        throw std::out_of_range("Too many columns to construct 9x9 grid");
      this->setFixedCellValue(num, row_index, col_index);
      col_index++;
    }
    if (col_index < 8)
      throw std::out_of_range("Too few columns to construct 9x9 grid");
    col_index = 0;
    row_index++;
  }
  if (row_index < 8)
    throw std::out_of_range("Too few rows to construct 9x9 grid");
}

void SudokuPuzzle::reset()
{
  std::fill(&grid[0][0], &grid[0][0] + 9 * 9, 0);
  std::fill(&fixedGrid[0][0], &fixedGrid[0][0] + 9 * 9, false);
}

int SudokuPuzzle::getCellValue(int row, int col) const
{
  if (row > 8 || row < 0)
    throw std::out_of_range("Row index is out of range: " + std::to_string(row));

  if (col > 8 || col < 0)
    throw std::out_of_range("Column index is out of range: " + std::to_string(col));

  return grid[row][col];
}

void SudokuPuzzle::setCellValue(int num, int row, int col)
{
  if (row > 8 || row < 0)
    throw std::out_of_range("Row index is out of range: " + std::to_string(row));

  if (col > 8 || col < 0)
    throw std::out_of_range("Column index is out of range: " + std::to_string(col));

  if (!fixedGrid[row][col])
    grid[row][col] = num;
}

void SudokuPuzzle::setFixed(bool fixed, int row, int col)
{
  if (row > 8 || row < 0)
    throw std::out_of_range("Row index is out of range: " + std::to_string(row));

  if (col > 8 || col < 0)
    throw std::out_of_range("Column index is out of range: " + std::to_string(col));

  fixedGrid[row][col] = fixed;
}

void SudokuPuzzle::setFixedCellValue(int num, int row, int col)
{
  if (row > 8 || row < 0)
    throw std::out_of_range("Row index is out of range: " + std::to_string(row));

  if (col > 8 || col < 0)
    throw std::out_of_range("Column index is out of range: " + std::to_string(col));

  setCellValue(num, row, col);
  setFixed(true, row, col);
}
