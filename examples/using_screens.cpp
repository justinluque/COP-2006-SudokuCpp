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
  screen.refresh();
  screen.handleInput();

  return 0;
}
