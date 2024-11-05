#pragma once

#include <memory>
#include "Screen.h"
#include "App.h"

enum class WindowType
{
  Home,
  Puzzle
};

class ScreenManager
{
public:
  ScreenManager();

  void refresh();
  void handleInput();

  void switchWindow(AppScreen screenType);

private:
  std::unique_ptr<Screen> currentScreen;
};
