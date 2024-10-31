#include <initializer_list>
#pragma once

class SudokuPuzzle
{
public:
  SudokuPuzzle();

  SudokuPuzzle(std::initializer_list<std::initializer_list<int>> grid);

  void reset();

  int getCellValue(int row, int col) const;

  void setCellValue(int num, int row, int col);

private:
  int grid[9][9];
};