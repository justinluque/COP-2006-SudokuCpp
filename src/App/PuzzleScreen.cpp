#include "PuzzleScreen.h"

#include <string>

#include "SudokuGenerator.h"
#include "SudokuSolver.h"
#include "Macro.h"

//  void generatePuzzle(); // CTRL_N
//   void checkPuzzle();    // CTRL_C
//   void solvePuzzle();    // CTRL_S
//   void giveHint();       // CTRL_H
//   void quit();           // CTRL_Q

PuzzleScreen::PuzzleScreen(std::function<void(ScreenAction)> screenActionCallback, PuzzleDifficulty difficulty) : Screen(screenActionCallback), screenActionCallback(screenActionCallback)
{
  // Clear previous screen
  clear();
  refresh();

  // Set the size of our main window
  sizeY = 17;
  sizeX = 70;

  // cellsize
  cellSize = 3;

  // grid start pos relative to main win
  gridStartY = 1;
  gridStartX = 2;

  // grid size
  gridSizeX = 32;
  gridSizeY = 13;

  // Help area size and start

  helpStartY = 2;
  helpStartX = gridStartX + gridSizeX + 2;

  helpSizeX = 30;
  helpSizeY = 13;

  // current cell starts at (4, 4)
  currentCellY = 4;
  currentCellX = 4;

  // Get screen dimensions
  int screenY = getmaxy(stdscr);
  int screenX = getmaxx(stdscr);

  // Calculate top-left corner coordinates to center the window
  int startY = (screenY - sizeY) / 2;
  int startX = (screenX - sizeX) / 2;

  window = newwin(sizeY, sizeX, startY, startX); // Full-screen window for resize prompt
  subHelpWindow = nullptr;

  keypad(window, true); /// Enable keypad inputs for our window

  switch (difficulty)
  {
  case PuzzleDifficulty::CUSTOM:
    currentPuzzle = SudokuGenerator::generateEmpty();
    break;

  case PuzzleDifficulty::EASY:
    currentPuzzle = SudokuGenerator::generateEasy();
    break;

  case PuzzleDifficulty::MEDIUM:
    currentPuzzle = SudokuGenerator::generateMedium();
    break;

  case PuzzleDifficulty::HARD:
    currentPuzzle = SudokuGenerator::generateHard();
    break;
  }

  drawGrid();

  drawHelp();

  drawSudokuNums();
}

PuzzleScreen::~PuzzleScreen()
{
  delwin(window);
  refreshScreen();
}

void PuzzleScreen::refreshScreen()
{
  drawSudokuNums();
  wrefresh(window);
}

void PuzzleScreen::handleInput()
{
  int key = wgetch(window);

  switch (key)
  {
  case KEY_UP:
    if (currentCellY == 0)
      currentCellY = 8;
    else
      currentCellY--;
    break;

  case KEY_DOWN:
    currentCellY = (currentCellY + 1) % 9;
    break;

  case KEY_LEFT:
    if (currentCellX == 0)
      currentCellX = 8;
    else
      currentCellX--;
    break;

  case KEY_RIGHT:
    currentCellX = (currentCellX + 1) % 9;
    break;

  case CTRL_X:
    screenActionCallback(ScreenAction::QUIT);
    break;

  case CTRL_S:
    currentPuzzle = SudokuSolver::solveBacktracking(currentPuzzle);
    break;

  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    currentPuzzle->setCellValue(key - '0', currentCellY, currentCellX);
  }
}

void PuzzleScreen::drawGrid()
{
  int rowsDrawn = 0, colsDrawn = 0;
  for (int row = 0; row <= 9; row++)
  {
    for (int column = 0; column <= 9; column++)
    {
      if (column % 3 == 0 && row != 0)
      {
        mvwprintw(window, rowsDrawn + gridStartY, colsDrawn + gridStartX, "|");
        colsDrawn++;
      }
      colsDrawn += cellSize;
    }
    rowsDrawn++;
    colsDrawn = 0;
    if (row % 3 == 0)
    {
      mvwprintw(window, rowsDrawn + gridStartY, colsDrawn + gridStartX, "+---------+---------+---------+");
      rowsDrawn++;
    }
  }
}

void PuzzleScreen::drawNumByPos(int num, int row, int col)
{
  int trueRow = (row / 3 + 2) + row + gridStartY;
  int trueCol = col / 3 + 2 + col * 3 + gridStartX;

  if (row == currentCellY && col == currentCellX)
    highlightOn();
  if (num == 0)
    mvwprintw(window, trueRow, trueCol, "-");
  else
    mvwprintw(window, trueRow, trueCol, "%d", num);
  if (row == currentCellY && col == currentCellX)
    highlightOff();
}

void PuzzleScreen::drawSudokuNums()
{
  box(window, 0, 0);

  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
      drawNumByPos(currentPuzzle->getCellValue(i, j), i, j);
  }
}

void PuzzleScreen::drawHelp()
{
  if (subHelpWindow == nullptr)
  {
    subHelpWindow = derwin(window, helpSizeY, helpSizeX, helpStartY, helpStartX);
  }
  box(subHelpWindow, 0, 0);

  std::string title = "Controls";

  std::string Navigation = "Navigate using arrow keys";
  std::string sCtrl_S = "CTRL-S: Solve puzzle";
  std::string sCtrl_M = "CTRL-M: Main Menu   ";
  std::string sCtrl_X = "CTRL-X: Exit        ";

  mvwprintw(subHelpWindow, 1, (helpSizeX - title.size()) / 2, title.data());
  mvwprintw(subHelpWindow, 3, (helpSizeX - Navigation.size()) / 2, Navigation.data());
  mvwprintw(subHelpWindow, 6, (helpSizeX - sCtrl_S.size()) / 2, sCtrl_S.data());
  mvwprintw(subHelpWindow, 7, (helpSizeX - sCtrl_X.size()) / 2, sCtrl_X.data());

  wrefresh(subHelpWindow);
}

void PuzzleScreen::highlightOn()
{
  wattr_on(window, COLOR_PAIR(HIGHLIGHT_COLOR_PAIR), 0);
}

void PuzzleScreen::highlightOff()
{
  wattr_off(window, COLOR_PAIR(HIGHLIGHT_COLOR_PAIR), 0);
}
