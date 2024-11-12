#include "HomeScreen.h"

#include "Enum.h"

HomeScreen::HomeScreen(std::function<void(AppScreen)> switchScreenCallback) : Screen(switchScreenCallback), switchScreenCallback(switchScreenCallback)
{
  // Clear previous screen
  clear();
  refresh();

  // Set the size of our main window
  sizeY = 30;
  sizeX = 60;

  // Get screen dimensions
  int screenY = getmaxy(stdscr);
  int screenX = getmaxx(stdscr);

  // Calculate top-left corner coordinates to center the window
  int startY = (screenY - sizeY) / 2;
  int startX = (screenX - sizeX) / 2;

  // Draw the main window if possible
  if (windowIsOutOfBounds())
  {
    window = newwin(screenY, screenX, 0, 0); // Full-screen window for resize prompt
    drawResizePrompt();
  }
  else
  {
    window = newwin(sizeY, sizeX, startY, startX); // Centered window
    drawMainWindow();
  }

  // Display the window
  wrefresh(window);
}

HomeScreen::~HomeScreen()
{
  delwin(window); // Free up any resources used by the window
}

void HomeScreen::refreshScreen()
{
  wrefresh(window); // Refresh the window
}

void HomeScreen::handleInput()
{
  wgetch(window); // Gets a character from input
}

void HomeScreen::drawMainWindow()
{
  box(window, 0, 0);

  int ascii_width = 50;

  int ascii_start = (sizeX - ascii_width) / 2;

  // Print the ASCII art inside the window
  mvwprintw(window, 1, ascii_start, "                                                 ");
  mvwprintw(window, 2, ascii_start, " _____         _       _         _____           ");
  mvwprintw(window, 3, ascii_start, "|   __| _ _  _| | ___ | |_  _ _ |     | ___  ___ ");
  mvwprintw(window, 4, ascii_start, "|__   || | || . || . || '_|| | ||   --|| . || . |");
  mvwprintw(window, 5, ascii_start, "|_____||___||___||___||_,_||___||_____||  _||  _|");
  mvwprintw(window, 6, ascii_start, "                                       |_|  |_|  ");

  int optionsStart = sizeY * 9 / 16;
  mvwprintw(window, optionsStart, 2, "Generate easy puzzle");
  mvwprintw(window, optionsStart + 2, 2, "Generate medium puzzle");
  mvwprintw(window, optionsStart + 4, 2, "Generate hard puzzle");
  mvwprintw(window, optionsStart + 6, 2, "Enter custom puzzle");
}

void HomeScreen::drawResizePrompt()
{
  mvwprintw(window, 0, 0, "Please resize the terminal and restart the program.");
}

bool HomeScreen::windowIsOutOfBounds()
{
  int maxY, maxX;
  getmaxyx(stdscr, maxY, maxX); // Get the max size of the term

  return sizeY > maxY || sizeX > maxX; // Compare the size to the size of our window
}
