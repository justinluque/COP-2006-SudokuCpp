#include "HomeScreen.h"

#include <array>
#include <string_view>

#include "Enum.h"
#include "Macro.h"

constexpr std::array<std::string_view, 4> options = {
    "Generate easy puzzle",
    "Generate medium puzzle",
    "Generate hard puzzle",
    "Enter custom puzzle",
};

HomeScreen::HomeScreen(std::function<void(ScreenAction)> screenActionCallback) : Screen(screenActionCallback), currentOption(0), screenActionCallback(screenActionCallback)
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

    keypad(window, true); /// Enable keypad inputs for our window

    drawConstantMainWindow();

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
  drawMainWindow();

  wrefresh(window); // Refresh the window
}

void HomeScreen::handleInput()
{
  int key = wgetch(window);

  switch (key)
  {
  case KEY_UP:
    if (currentOption == 0)
      currentOption = 3;
    else
      currentOption--;
    break;

  case KEY_DOWN:
    currentOption = (currentOption + 1) % 4;
    break;

  case CTRL_X:
    endwin(); // TODO: define quit behavior.
    break;

  case KEY_ENTER:
    break; // TODO: define pick behavior.
           //        likely will create an action function instead of passing many different bindings
  }
}

void HomeScreen::drawMainWindow()
{

  int optionsStartY = sizeY * 9 / 16;

  for (size_t i = 0; i < 4; i++)
  {
    if (i == currentOption)
      highlightOn();
    mvwprintw(window, optionsStartY + i * 2, (sizeX - options[i].length()) / 2, options[i].data());
    if (i == currentOption)
      highlightOff();
  }

  wrefresh(window);
}

void HomeScreen::drawConstantMainWindow()
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

  mvwprintw(window, 8, (sizeX - 30) / 2, "Sebastian Diaz & Justin Luque");
}
void HomeScreen::drawResizePrompt()
{
  mvwprintw(window, 0, 0, "Please resize the terminal and restart the program.");
}

void HomeScreen::highlightOn()
{
  wattr_on(window, COLOR_PAIR(HIGHLIGHT_COLOR_PAIR), 0);
}

void HomeScreen::highlightOff()
{
  wattr_off(window, COLOR_PAIR(HIGHLIGHT_COLOR_PAIR), 0);
}

bool HomeScreen::windowIsOutOfBounds()
{
  int maxY, maxX;
  getmaxyx(stdscr, maxY, maxX); // Get the max size of the term

  return sizeY > maxY || sizeX > maxX; // Compare the size to the size of our window
}
