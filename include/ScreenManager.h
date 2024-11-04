#pragma once

#include <memory>
#include "Screen.h"

enum class WindowType
{
  Home,
  Puzzle
};

class ScreenManager
{
public:
  ScreenManager();
  ~ScreenManager();

  void refresh();
  void switchWindow(WindowType window);

private:
  WindowType currentWindowType;
  std::unique_ptr<Screen> currentScreen;
};
