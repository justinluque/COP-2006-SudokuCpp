#include "PuzzleScreen.h"

#include "SudokuGenerator.h"
#include "Macro.h"

//  void generatePuzzle(); // CTRL_N
//   void checkPuzzle();    // CTRL_C
//   void solvePuzzle();    // CTRL_S
//   void giveHint();       // CTRL_H
//   void quit();           // CTRL_Q

PuzzleScreen::PuzzleScreen(std::function<void(ScreenAction)> screenActionCallback) : Screen(screenActionCallback), screenActionCallback(screenActionCallback), currentPuzzle(SudokuGenerator::generateEasy())
{
  // Clear previous screen
  clear();
  refresh();

  // Set the size of our main window
  sizeY = 30;
  sizeX = 80;

  // Get screen dimensions
  int screenY = getmaxy(stdscr);
  int screenX = getmaxx(stdscr);

  // Calculate top-left corner coordinates to center the window
  int startY = (screenY - sizeY) / 2;
  int startX = (screenX - sizeX) / 2;

  window = newwin(sizeY, sizeX, startY, startX); // Full-screen window for resize prompt

  keypad(window, true); /// Enable keypad inputs for our window

  drawGrid();
}

PuzzleScreen::~PuzzleScreen()
{
  delwin(window);
  refreshScreen();
}

void PuzzleScreen::refreshScreen()
{
  wrefresh(window);
}

void PuzzleScreen::handleInput() {}

// void App::handleInput()
// {
//   int key = getch();
//   switch (key)
//   {
//   case CTRL_N:
//     generatePuzzle();
//     break;

//   case CTRL_C:
//     checkPuzzle();
//     break;

//   case CTRL_S:
//     solvePuzzle();
//     break;

//   case CTRL_H:
//     giveHint();
//     break;

//   case CTRL_X:
//     quit();
//     break;

//   // TODO: define arrow key behavior
//   case KEY_UP:
//     break;

//   case KEY_DOWN:
//     break;

//   case KEY_LEFT:
//     break;

//   case KEY_RIGHT:
//     break;

//   case '0':
//   case '1':
//   case '2':
//   case '3':
//   case '4':
//   case '5':
//   case '6':
//   case '7':
//   case '8':
//   case '9':
//     currentPuzzle->setCellValue(key - '0', currentRow, currentCol);
//     break;
//   }
// }

void PuzzleScreen::drawGrid()
{
  int startY = 0, startX = 0;
  int cellSize = 3;

  int rowsDrawn = 0, colsDrawn = 0;
  for (int row = 0; row <= 9; row++)
  {
    for (int column = 0; column <= 9; column++)
    {
      if (column % 3 == 0 && row != 0)
      {
        mvwprintw(window, rowsDrawn, colsDrawn, "|");
        colsDrawn++;
      }
      colsDrawn += cellSize;
    }
    rowsDrawn++;
    colsDrawn = 0;
    if (row % 3 == 0)
    {
      mvwprintw(window, rowsDrawn, colsDrawn, "+---------+---------+---------+");
      rowsDrawn++;
    }
  }
}

void PuzzleScreen::drawMainWindow()
{
}

void PuzzleScreen::highlightOn()
{
  wattr_on(window, COLOR_PAIR(HIGHLIGHT_COLOR_PAIR), 0);
}

void PuzzleScreen::highlightOff()
{
  wattr_off(window, COLOR_PAIR(HIGHLIGHT_COLOR_PAIR), 0);
}
