#include "ScreenManager.h"

#include <memory>
#include <functional>

#include "HomeScreen.h"
#include "PuzzleScreen.h"

ScreenManager::ScreenManager()
{
  currentScreen = nullptr;
}

void ScreenManager::refresh()
{
  if (currentScreen)
    currentScreen->refresh();
}

void ScreenManager::handleInput()
{
  if (currentScreen)
    currentScreen->handleInput();
}

void ScreenManager::switchWindow(AppScreen screenType)
{
  // Create a std::function from a member function
  std::function<void(AppScreen)> func = std::bind(&ScreenManager::switchWindow, this, std::placeholders::_1);

  switch (screenType)
  {
  case AppScreen::HOME:
    currentScreen = std::make_unique<HomeScreen>(func);
    break;

  case AppScreen::PUZZLE:
    currentScreen = std::make_unique<PuzzleScreen>(func);
    break;
  }
}
