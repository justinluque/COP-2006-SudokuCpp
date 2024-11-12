#pragma once

#include <memory>

#include "Screen.h"
#include "Enum.h"

class ScreenManager
{
public:
  ScreenManager();

  void refreshCurrentScreen();
  void handleInput();

  void switchWindow(AppScreen screenType);

private:
  std::unique_ptr<Screen> currentScreen;
};
