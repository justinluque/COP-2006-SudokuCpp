#pragma once

#include <memory>

#include "Screen.h"
#include "Enum.h"

class ScreenManager
{
public:
  ScreenManager(AppState &appState);

  void refreshCurrentScreen();
  void handleInput();

  void switchWindow(AppScreen screenType);

  void doScreenAction(ScreenAction screenAction);

private:
  AppState &mainAppState;
  std::unique_ptr<Screen> currentScreen;
};
