#include "App.h"

#include <ncurses.h>

#include "SudokuSolver.h"
#include "SudokuGenerator.h"
#include "Macro.h"

App::App() : screenManager(nullptr)
{
  initializeCurses();

  screenManager = std::make_unique<ScreenManager>(currentState);

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
    screenManager->refreshCurrentScreen();
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

  // Hides the cursor
  curs_set(0);

  // Start color mode
  start_color();

  // Initialize color pairs
  init_pair(HIGHLIGHT_COLOR_PAIR, COLOR_BLACK, COLOR_WHITE);
  init_pair(CORRECT_COLOR_PAIR, COLOR_BLACK, COLOR_GREEN);
  init_pair(WRONG_COLOR_PAIR, COLOR_BLACK, COLOR_RED);
}

void App::destroyCurses()
{
  // Destroy ncurses environment and give back any memory
  endwin();
}
