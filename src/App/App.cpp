#include "App.h"

#include <ncurses/ncurses.h>
#include "SudokuSolver.h"
#include "SudokuGenerator.h"

#define CTRL_C 3
#define CTRL_H 8
#define CTRL_N 14
#define CTRL_S 19
#define CTRL_X 24

App::App() : currentScreen(AppScreen::HOME), screenManager(std::make_unique<ScreenManager>())
{
  initializeCurses();

  currentScreen = AppScreen::HOME;

  screenManager->switchWindow(currentScreen);
}

App::~App()
{
  destroyCurses();
}

void App::run()
{
  currentState = AppState::RUNNING;

  while (currentState == AppState::RUNNING)
  {
    screenManager->refresh();
    screenManager->handleInput();
  }
}

void App::initializeCurses()
{
  // Initializes curses environment
  initscr();

  // Makes user input immediately available without newline
  cbreak();

  // Turn off echoing of characters typed by the user
  noecho();

  // Turn on keypad inputs such as the arrow keys
  keypad(stdscr, true);
}

void App::destroyCurses()
{
  // Destroy ncurses environment and give back any memory
  endwin();
}
