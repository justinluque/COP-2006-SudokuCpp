#include "HomeScreen.h"

HomeScreen::HomeScreen()
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

HomeScreen::~HomeScreen()
{
  delwin(window);
}

void HomeScreen::refresh() {}

void HomeScreen::handleInput() {}
