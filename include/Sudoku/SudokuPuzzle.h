#pragma once

#include <initializer_list>

class SudokuPuzzle
{
public:
  SudokuPuzzle();

  SudokuPuzzle(std::initializer_list<std::initializer_list<int>> grid);

  void reset();

  int getCellValue(int row, int col) const;

  void setCellValue(int num, int row, int col);

  void strongSetValue(int num, int row, int col);

  void setFixedCellValue(int num, int row, int col);

  void setFixed(bool fixed, int row, int col);

private:
  int grid[9][9];
  bool fixedGrid[9][9];
};
