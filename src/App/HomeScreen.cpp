#include "HomeScreen.h"

#include "Enum.h"

HomeScreen::HomeScreen(std::function<void(AppScreen)> switchScreenCallback) : Screen(switchScreenCallback), switchScreenCallback(switchScreenCallback)
{
  clear();
  refresh();
  sizeY = 10;
  sizeX = 10;

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
  delwin(window);
}

void HomeScreen::refreshScreen()
{
  wrefresh(window);
}

void HomeScreen::handleInput()
{
  getch();
}

void HomeScreen::drawMainWindow()
{
  box(window, 0, 0);
  mvwprintw(window, 1, 1, "MAINWINDOW");
}

void HomeScreen::drawResizePrompt()
{
  mvwprintw(window, 0, 0, "Please resize the terminal and restart the program.");
}

bool HomeScreen::windowIsOutOfBounds()
{
  int maxY, maxX;
  getmaxyx(stdscr, maxY, maxX);

  return sizeY > maxY || sizeX > maxX;
}
