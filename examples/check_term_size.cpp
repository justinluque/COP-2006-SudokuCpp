#include <ncurses/ncurses.h>

int main()
{
  initscr();            // Initialize ncurses
  cbreak();             // Disable line buffering
  noecho();             // Don't echo user input
  keypad(stdscr, TRUE); // Enable special keys (e.g., arrow keys)

  int maxY, maxX;
  getmaxyx(stdscr, maxY, maxX); // Get screen dimensions

  mvprintw(0, 0, "%d Y %d X", maxY, maxX); // Print screen size
  refresh();                               // Refresh the screen to show the printed text

  getch(); // Wait for user input

  clear();
  refresh();

  // Create a new window at (0, 0) with dimensions 10x10
  WINDOW *window = newwin(10, 10, 0, 0);
  box(window, 0, 0);                   // Draw a border around the window
  mvwprintw(window, 0, 1, "box test"); // Print text in the window
  mvwprintw(window, 1, 1, "HI!");      // Print more text in the window

  wrefresh(window); // Refresh the window to display the content

  getch(); // Wait for user input

  endwin(); // End ncurses

  return 0;
}
