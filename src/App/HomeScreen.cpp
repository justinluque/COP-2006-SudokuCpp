#include "HomeScreen.h"

#include "Enum.h"

HomeScreen::HomeScreen(std::shared_ptr<ScreenManager> screenManager) : Screen(screenManager)
{
  int maxY, maxX;
  getmaxyx(stdscr, maxX, maxY);

  int startY = maxY / 4;
  int startX = maxX / 4;

  window = newwin(startY, startX, maxY, maxX);
  box(window, 0, 0);
  wrefresh(window);
}

HomeScreen::~HomeScreen()
{
  delwin(window);
}

void HomeScreen::refresh()
{
  wrefresh(window);
}

void HomeScreen::handleInput() {}
