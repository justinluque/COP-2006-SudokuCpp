#include "PuzzleScreen.h"

//  void generatePuzzle(); // CTRL_N
//   void checkPuzzle();    // CTRL_C
//   void solvePuzzle();    // CTRL_S
//   void giveHint();       // CTRL_H
//   void quit();           // CTRL_Q

PuzzleScreen::PuzzleScreen(std::shared_ptr<ScreenManager> screenManager) : Screen(screenManager)
{
  int maxY, maxX;
  getmaxyx(stdscr, maxX, maxY);

  int startY = maxY / 4;
  int startX = maxX / 4;

  window = newwin(startY, startX, maxY, maxX);
  box(window, 0, 0);
  refresh();
  wrefresh(window);
}

PuzzleScreen::~PuzzleScreen()
{
  delwin(window);
  refresh();
}

void PuzzleScreen::refresh()
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
