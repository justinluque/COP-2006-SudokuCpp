#include "App.h"

#include <ncurses/ncurses.h>
#include "SudokuSolver.h"
#include "SudokuGenerator.h"

App::App() : screenManager(std::make_shared<ScreenManager>())
{
  initializeCurses();

  screenManager->switchWindow(AppScreen::HOME);
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
