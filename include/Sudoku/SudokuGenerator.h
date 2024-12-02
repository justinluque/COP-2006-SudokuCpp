#pragma once

#include <memory>

#include "SudokuPuzzle.h"

/**
 * SudokuGenerator
 *
 * The SudokuGenerator class is a static class responsible for generating
 * sudoku puzzles of various difficulities using a variation of the main solving algorithm
 *
 * Each difficulty generator uses the same private generate(int clues) method to generate
 * a puzzle and then selecting a random number of clues within the specified difficulty range.
 *
 * The generate(int clues) method is a variation that uses random number generation to more randomly
 * fill the empty puzzle with clues.
 *
 * Then, the method randomly deletes clues while checking that the puzzle remains valid until
 * a puzzle with the given number of clues is produced.
 *
 * To ensure the puzzle remains valid, generate(int clues) uses a few methods from SudokuSolver to determine
 * if the puzzle respects the rules of Sudoku and if the puzzle has a single, unique solution.
 */

class SudokuGenerator
{
public:
  SudokuGenerator() = delete;

  // Generate a sudoku puzzle with 36-50 clues
  static std::unique_ptr<SudokuPuzzle> generateEasy();

  // Generate a sudoku puzzle with 32-35 clues
  static std::unique_ptr<SudokuPuzzle> generateMedium();

  // Generate a puzzle with 28-31 clues
  static std::unique_ptr<SudokuPuzzle> generateHard();

  // Create an empty puzzle
  static std::unique_ptr<SudokuPuzzle> generateEmpty();

private:
  // Attempt to generate a unique puzzle with the given number of clues
  static std::unique_ptr<SudokuPuzzle> generate(int clues);

  /* Helper algorithm similar to the solving algorithm that uses random filling instead of in-order
   * to achieve random puzzle generation */
  static bool randomlyFillPuzzle(std::unique_ptr<SudokuPuzzle> &puzzle, int row, int col);
};
