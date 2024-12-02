#include "HomeScreen.h"

#include <array>
#include <string_view>

#include "Enum.h"
#include "Macro.h"

namespace
{
  constexpr std::array<std::string_view, static_cast<size_t>(HomeScreenOption::COUNT)>
      options = {
          "Generate easy puzzle",
          "Generate medium puzzle",
          "Generate hard puzzle",
          "Enter custom puzzle",
          "Quit",
  };

  std::string_view HomeScreenOptionToString(HomeScreenOption option)
  {
    return options[static_cast<size_t>(option)];
  }
}

HomeScreen::HomeScreen(std::function<void(ScreenAction)> screenActionCallback) : Screen(screenActionCallback), selectedOption(HomeScreenOption::GENERATE_EASY)
{
  // Clear previous screen
  clear();
  refresh();

  // Set the size of our main window
  sizeY = 30;
  sizeX = 60;

  // Get screen dimensions
  const int screenY = getmaxy(stdscr);
  const int screenX = getmaxx(stdscr);

  // Calculate top-left corner coordinates to center the window
  const int startY = (screenY - sizeY) / 2;
  const int startX = (screenX - sizeX) / 2;

  // Draw the main window if possible
  if (windowIsOutOfBounds())
  {
    window = newwin(screenY, screenX, 0, 0); // Full-screen window for resize prompt
    drawResizePrompt();
    wgetch(window);
    screenActionCallback(ScreenAction::QUIT);
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
  const int key = wgetch(window);
  size_t optionCode = static_cast<int>(selectedOption);

  const int maxSelectableOption = static_cast<int>(HomeScreenOption::COUNT) - 1;

  switch (key)
  {
  case KEY_UP:
    optionCode = (optionCode + maxSelectableOption) % (maxSelectableOption + 1);
    selectedOption = static_cast<HomeScreenOption>(optionCode);
    break;

  case KEY_DOWN:
    optionCode = (optionCode + 1) % (maxSelectableOption + 1);
    selectedOption = static_cast<HomeScreenOption>(optionCode);
    break;

  case CTRL_X:
    screenActionCallback(ScreenAction::QUIT);
    break;

  case ENTER:
    switch (selectedOption) // Perform an action depending on the selected option
    {
    case HomeScreenOption::GENERATE_EASY:
      screenActionCallback(ScreenAction::GENERATE_EASY);
      break;

    case HomeScreenOption::GENERATE_MEDIUM:
      screenActionCallback(ScreenAction::GENERATE_MEDIUM);
      break;

    case HomeScreenOption::GENERATE_HARD:
      screenActionCallback(ScreenAction::GENERATE_HARD);
      break;

    case HomeScreenOption::ENTER_CUSTOM:
      screenActionCallback(ScreenAction::ENTER_CUSTOM);
      break;

    case HomeScreenOption::QUIT:
      screenActionCallback(ScreenAction::QUIT);
      break;

    case HomeScreenOption::COUNT:
      break;
    }
  }
}

void HomeScreen::drawMainWindow()
{
  const int optionsStartY = sizeY * 9 / 16;

  for (size_t optionIterator = 0; optionIterator < static_cast<size_t>(HomeScreenOption::COUNT); optionIterator++)
  {
    HomeScreenOption currentOption = static_cast<HomeScreenOption>(optionIterator);
    if (currentOption == selectedOption)
      highlightOn();
    mvwprintw(window, optionsStartY + optionIterator * 2, (sizeX - options[optionIterator].length()) / 2, HomeScreenOptionToString(currentOption).data());
    if (currentOption == selectedOption)
      highlightOff();
  }

  wrefresh(window);
}

void HomeScreen::drawConstantMainWindow()
{
  box(window, 0, 0);

  const int ascii_width = 50;

  const int ascii_start = (sizeX - ascii_width) / 2;

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
