#include "PuzzleScreen.h"

PuzzleScreen::PuzzleScreen()
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

void PuzzleScreen::refresh() {}

void PuzzleScreen::handleInput() {}
