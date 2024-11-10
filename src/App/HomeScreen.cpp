#include "HomeScreen.h"

#include "Enum.h"

HomeScreen::HomeScreen(std::function<void(AppScreen)> switchScreenCallback) : Screen(switchScreenCallback), switchScreenCallback(switchScreenCallback)
{
  sizeY = 5;
  sizeX = 5;

  if (windowIsOutOfBounds())
  {
    window = newwin(getmaxy(stdscr), getmaxx(stdscr), 0, 0);
    drawResizePrompt();
  }
  else
  {
    window = newwin(sizeY, sizeX, 0, 0);
    drawMainWindow();
  }

  wrefresh(window);
}

HomeScreen::~HomeScreen()
{
  wclear(window);
  wrefresh(window);
  delwin(window);
}

void HomeScreen::refresh()
{
  wrefresh(window);
}

void HomeScreen::handleInput()
{
  switch (getch())
  {
  }
}

void HomeScreen::drawMainWindow()
{
  wclear(window);
  box(window, 0, 0);
  mvwprintw(window, 1, 1, "MAINWINDOW");
}

void HomeScreen::drawResizePrompt()
{
  wclear(window);
  mvwprintw(window, 0, 0, "Please resize the terminal and restart the program.");
}

bool HomeScreen::windowIsOutOfBounds()
{
  int maxY, maxX;
  getmaxyx(stdscr, maxY, maxX);

  return sizeY > maxY || sizeX > maxX;
}
