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
  if (currentScreen && mainAppState == AppState::RUNNING)
    currentScreen->refreshScreen();
}

void ScreenManager::handleInput()
{
  if (currentScreen && mainAppState == AppState::RUNNING)
    currentScreen->handleInput();
}

void ScreenManager::doScreenAction(ScreenAction screenAction)
{
  switch (screenAction)
  {
  case ScreenAction::QUIT:
    mainAppState = AppState::EXITING;
    break;

  case ScreenAction::GENERATE_EASY:
    switchWindow(AppScreen::PUZZLE, PuzzleDifficulty::EASY);
    break;

  case ScreenAction::GENERATE_MEDIUM:
    switchWindow(AppScreen::PUZZLE, PuzzleDifficulty::MEDIUM);
    break;

  case ScreenAction::GENERATE_HARD:
    switchWindow(AppScreen::PUZZLE, PuzzleDifficulty::HARD);
    break;

  case ScreenAction::ENTER_CUSTOM:
    switchWindow(AppScreen::PUZZLE, PuzzleDifficulty::CUSTOM);
    break;

  case ScreenAction::MAIN_MENU:
    switchWindow(AppScreen::HOME);
    break;

  case ScreenAction::COUNT:
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
    currentScreen = std::make_unique<PuzzleScreen>(screenActionCallback, PuzzleDifficulty::CUSTOM);
    break;
  }
}

void ScreenManager::switchWindow(AppScreen screenType, PuzzleDifficulty difficulty)
{
  // Create a std::function from a member function
  std::function<void(ScreenAction)> screenActionCallback = std::bind(&ScreenManager::doScreenAction, this, std::placeholders::_1);

  switch (screenType)
  {
  case AppScreen::HOME:
    currentScreen = std::make_unique<HomeScreen>(screenActionCallback);
    break;

  case AppScreen::PUZZLE:
    currentScreen = std::make_unique<PuzzleScreen>(screenActionCallback, difficulty);
    break;
  }
}
