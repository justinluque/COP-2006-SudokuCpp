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

void ScreenManager::switchWindow(AppScreen screenType)
{
  switch (screenType)
  {
  case AppScreen::HOME:
    currentScreen = std::make_unique<HomeScreen>();

  case AppScreen::PUZZLE:
    currentScreen = std::make_unique<PuzzleScreen>();
  }
}
