#pragma once

#include <memory>

#include "SudokuPuzzle.h"

/**
 * SudokuSolver
 *
 * The SudokuSolver class is a static class responsible for finding solutions
 * to sudoku puzzles, mainly through recursive backtracking algorithms
 *
 * This class also provides a few extra methods tied to sudoku solving algorithms
 * such as isFull(), isValid() and isSolved()
 */

class SudokuSolver
{
public:
  SudokuSolver() = delete;

  /**
   * Wrapper method for the recursiveAlgorithm() that
   *  attempts to solve the passed puzzle and returns
   *  the solution
   */
  static std::unique_ptr<SudokuPuzzle> solveBacktracking(const std::unique_ptr<SudokuPuzzle> &puzzle);

  /**
   * Determines whether the given sudoku puzzle respects
   * the rules of sudoku (each row, column and 3x3 subgrid
   * must contain each number 1-9 non-repeating)
   */
  static bool isValid(const std::unique_ptr<SudokuPuzzle> &puzzle);

  /**
   * Determines if the given sudoku puzzle is full or if it
   * contains any empty cells
   */
  static bool isFull(const std::unique_ptr<SudokuPuzzle> &puzzle);

  /**
   * Combines isValid() and isFull() to determine if the puzzle
   * is solved
   */
  static bool isSolved(const std::unique_ptr<SudokuPuzzle> &puzzle);

  /**
   * Determines whether the given sudoku puzzle has a single, unique solution
   * If the puzzle has multiple solutions or none the method returns false
   */
  static bool hasUniqueSolution(const std::unique_ptr<SudokuPuzzle> &puzzle);

  /**
   * Determines if the given number at the given row and column is a correct placement
   * in the given puzzle according to the rules of sudoku
   */
  static bool isCorrectPlacement(const std::unique_ptr<SudokuPuzzle> &puzzle, int num, int row, int col);

private:
  /**
   * Recursive backtracking algorithm that iterates through the puzzle until
   * it finds an empty cell, tries placing numbers 1-9 in the cell until it finds
   * a number that respects the rules of sudoku. The algorithm then continues
   * the same process and backtracks if necessary
   *
   * The algorithm continues until the puzzle is solved or all possible paths
   * to solution are exhausted
   */
  static bool recursiveAlgorithm(std::unique_ptr<SudokuPuzzle> &puzzle, int row, int col);

  /**
   * Similar to the recursive algorithm but instead sets a flag to true if a solution is found and
   * then attempts to find another. If another different solution is found, return true.
   */
  static bool findSecondSolution(std::unique_ptr<SudokuPuzzle> &puzzle, int row, int col, bool &solutionFound);
};
