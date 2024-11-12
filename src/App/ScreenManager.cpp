#include "ScreenManager.h"

#include <memory>
#include <functional>

#include "HomeScreen.h"
#include "PuzzleScreen.h"

ScreenManager::ScreenManager(AppState &appState) : mainAppState(appState)
{
  currentScreen = nullptr;
}

void ScreenManager::refreshCurrentScreen()
{
  if (currentScreen)
    currentScreen->refreshScreen();
}

void ScreenManager::handleInput()
{
  if (currentScreen)
    currentScreen->handleInput();
}

void ScreenManager::doScreenAction(ScreenAction screenAction)
{
  switch (screenAction)
  {
  case ScreenAction::QUIT:
    mainAppState = AppState::EXITING;
    break;

  // TODO: complete puzzle screen
  case ScreenAction::GENERATE_EASY:
    switchWindow(AppScreen::PUZZLE);
    break;

  case ScreenAction::GENERATE_MEDIUM:
    switchWindow(AppScreen::PUZZLE);
    break;

  case ScreenAction::GENERATE_HARD:
    switchWindow(AppScreen::PUZZLE);
    break;

  case ScreenAction::INPUT_CUSTOM:
    switchWindow(AppScreen::PUZZLE);
    break;
  }
}

void ScreenManager::switchWindow(AppScreen screenType)
{
  // Create a std::function from a member function
  std::function<void(ScreenAction)> screenActionCallback = std::bind(&ScreenManager::doScreenAction, this, std::placeholders::_1);

  switch (screenType)
  {
  case AppScreen::HOME:
    currentScreen = std::make_unique<HomeScreen>(screenActionCallback);
    break;

  case AppScreen::PUZZLE:
    currentScreen = std::make_unique<PuzzleScreen>(screenActionCallback);
    break;
  }
}
