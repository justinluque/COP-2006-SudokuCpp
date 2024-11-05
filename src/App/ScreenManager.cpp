#include "ScreenManager.h"

#include <memory>

#include "HomeScreen.h"
#include "PuzzleScreen.h"

ScreenManager::ScreenManager() : currentScreen(std::make_unique<HomeScreen>()) {}

void ScreenManager::refresh()
{
  currentScreen->refresh();
}

void ScreenManager::handleInput()
{
  currentScreen->handleInput();
}

void ScreenManager::switchWindow(WindowType windowType)
{
  switch (windowType)
  {
  case WindowType::Home:
    currentScreen = std::make_unique<HomeScreen>();

  case WindowType::Puzzle:
    currentScreen = std::make_unique<PuzzleScreen>();
  }
}
