#pragma once

class SudokuPuzzle
{
public:
  SudokuPuzzle();

  SudokuPuzzle(const int (&grid)[9][9]);

  void reset();

  int getCellValue(int row, int col) const;

  void setCellValue(int num, int row, int col);

private:
  int grid[9][9];
};