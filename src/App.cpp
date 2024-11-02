#include "App.h"

#include <curses.h>
#include "SudokuSolver.h"
#include "SudokuGenerator.h"

#define CTRL_C 3
#define CTRL_H 8
#define CTRL_N 14
#define CTRL_S 19
#define CTRL_X 24

App::App()
{
  initializeCurses();

  // TODO: welcome message then generate a puzzle

  generatePuzzle();
}

App::~App()
{
  destroyCurses();
}

void App::run()
{
  while (appState == AppState::RUNNING)
  {
    displayPuzzle();
    handleInput();
  }
}

void App::initializeCurses()
{
  // Initializes curses environment
  initscr();

  // Makes user input immediately available without newline
  cbreak();

  // Turn off echoing of characters typed by the user
  noecho();

  // Turn on keypad inputs such as the arrow keys
  keypad(stdscr, true);
}

void App::destroyCurses()
{
  // Destroy ncurses environment and give back any memory
  endwin();
}

void App::displayPuzzle()
{
  // TODO: create window and draw the puzzle.
}

void App::handleInput()
{
  char key = getch();
  switch (key)
  {
  case CTRL_N:
    generatePuzzle();
    break;

  case CTRL_C:
    checkPuzzle();
    break;

  case CTRL_S:
    solvePuzzle();
    break;

  case CTRL_H:
    giveHint();
    break;

  case CTRL_X:
    quit();
    break;

  // TODO: define arrow key behavior
  case KEY_UP:
    break;

  case KEY_DOWN:
    break;

  case KEY_LEFT:
    break;

  case KEY_RIGHT:
    break;

  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    currentPuzzle->setCellValue(key - '0', currentRow, currentCol);
    break;
  }
}

void App::generatePuzzle()
{
  // TODO: generate a new puzzle of given difficulty. will probably need to add a parameter
}

void App::checkPuzzle()
{
  // TODO: check the current puzzle to see if any cells are wrong
}

void App::solvePuzzle()
{
  std::unique_ptr<SudokuPuzzle> solvedPuzzle = SudokuSolver::solveBacktracking(currentPuzzle);

  // TODO: display the solved puzzle?
}

void App::giveHint()
{
  // TODO: should we just store the solved puzzle? instead of having to re-solve each time to display a hint?
  // TODO: maybe store once and then store it
}

void App::quit()
{
  // TODO: are you sure you want to quit?

  appState = AppState::EXITING;
}