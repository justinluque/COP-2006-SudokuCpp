#include <ncurses/ncurses.h>
#include "HomeScreen.h"
#include "Enum.h"

int main()
{
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);

  HomeScreen screen([](AppScreen) {});
  screen.refreshScreen();
  screen.handleInput();

  return 0;
}