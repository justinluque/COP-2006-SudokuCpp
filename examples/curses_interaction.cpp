#include <ncurses/ncurses.h>

int yMax, xMax;
int yTransform = 0, xTransform = 0;

void resize(WINDOW *halfWindow)
{
  getmaxyx(stdscr, yMax, xMax);
}

void refreshBox(WINDOW *halfWindow)
{
  delwin(halfWindow);
  halfWindow = newwin(yMax / 2 + yTransform, xMax / 2 + xTransform, yMax / 4, xMax / 4);
  box(halfWindow, 0, 0);
  wrefresh(halfWindow);
}

int main()
{
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);

  getmaxyx(stdscr, yMax, xMax);

  WINDOW *halfWindow = newwin(yMax / 2, xMax / 2, yMax / 4, xMax / 4);
  box(halfWindow, 0, 0);

  refresh();
  wrefresh(halfWindow);

  while (true)
  {

    switch (getch())
    {
    case KEY_RESIZE:
      resize(halfWindow);
      break;

    case KEY_LEFT:
      xTransform -= 1;
      break;
    case KEY_RIGHT:
      xTransform += 1;
      break;

    case KEY_DOWN:
      yTransform -= 1;
      break;

    case KEY_UP:
      yTransform += 1;
      break;
    }

    refreshBox(halfWindow);
  }

  endwin();

  return 0;
}
