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
  this->reset();

  if (grid.size() != 9)
    throw std::out_of_range("Expected nine rows to construct 9x9 grid");

  int rowIterator = 0;

  for (const std::initializer_list<int> &row : grid)
  {
    if (row.size() != 9)
      throw std::out_of_range("Expected nine columns to construct 9x9 grid");

    int columnIterator = 0;

    for (const int &num : row)
    {
      if (num < 0 || num > 9)
        throw std::out_of_range("Cell value not in range of 0-9");

      this->strongSetValue(num, rowIterator, columnIterator);
      if (num != 0)
        this->setFixed(true, rowIterator, columnIterator);

      columnIterator++;
    }
    rowIterator++;
  }
}

void SudokuPuzzle::reset()
{
  std::fill(&grid[0][0], &grid[0][0] + 9 * 9, 0);
  std::fill(&fixedGrid[0][0], &fixedGrid[0][0] + 9 * 9, false);
}

void SudokuPuzzle::resetToFixedCells()
{
  for (int row = 0; row < 9; row++)
    for (int col = 0; col < 9; col++)
      if (getFixed(row, col))
        setCellValue(0, row, col);
}

int SudokuPuzzle::getCellValue(int row, int col) const
{
  if (row < 0 || row > 8)
    throw std::out_of_range("Row index is out of range: " + std::to_string(row));

  if (col < 0 || col > 8)
    throw std::out_of_range("Column index is out of range: " + std::to_string(col));

  return grid[row][col];
}

void SudokuPuzzle::setCellValue(int num, int row, int col)
{
  if (row < 0 || row > 9)
    throw std::out_of_range("Row index is out of range: " + std::to_string(row));

  if (col < 0 || col > 9)
    throw std::out_of_range("Column index is out of range: " + std::to_string(col));

  if (num < 0 || num > 9)
    throw std::out_of_range("Value is out of range: " + std::to_string(num));

  if (!fixedGrid[row][col])
    grid[row][col] = num;
}

void SudokuPuzzle::setFixed(bool fixed, int row, int col)
{
  if (row < 0 || row > 8)
    throw std::out_of_range("Row index is out of range: " + std::to_string(row));

  if (col < 0 || col > 8)
    throw std::out_of_range("Column index is out of range: " + std::to_string(col));

  fixedGrid[row][col] = fixed;
}

bool SudokuPuzzle::getFixed(int row, int col) const
{
  if (row < 0 || row > 9)
    throw std::out_of_range("Row index is out of range: " + std::to_string(row));

  if (col < 0 || col > 9)
    throw std::out_of_range("Column index is out of range: " + std::to_string(col));

  return fixedGrid[row][col];
}

int SudokuPuzzle::getTotalClues() const
{
  int totalClues = 0;

  for (int row = 0; row < 9; row++)
    for (int col = 0; col < 9; col++)
      if (getFixed(row, col))
        totalClues++;

  return totalClues;
}

void SudokuPuzzle::strongSetValue(int num, int row, int col)
{
  if (row < 0 || row > 8)
    throw std::out_of_range("Row index is out of range: " + std::to_string(row));

  if (col < 0 || col > 8)
    throw std::out_of_range("Column index is out of range: " + std::to_string(col));

  if (num < 0 || num > 9)
    throw std::out_of_range("Value is out of range: " + std::to_string(num));

  grid[row][col] = num;
}

void SudokuPuzzle::setFixedCellValue(int num, int row, int col)
{
  if (row < 0 || row > 8)
    throw std::out_of_range("Row index is out of range: " + std::to_string(row));

  if (col < 0 || col > 8)
    throw std::out_of_range("Column index is out of range: " + std::to_string(col));

  if (num < 0 || num > 9)
    throw std::out_of_range("Value is out of range: " + std::to_string(num));

  setCellValue(num, row, col);
  setFixed(true, row, col);
}

void SudokuPuzzle::lockPuzzle()
{
  for (int row = 0; row < 9; row++)
    for (int col = 0; col < 9; col++)
      setFixed(true, row, col);
}

void SudokuPuzzle::unlockPuzzle()
{
  for (int row = 0; row < 9; row++)
    for (int col = 0; col < 9; col++)
      setFixed(false, row, col);
}
