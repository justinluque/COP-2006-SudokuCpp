#pragma once

#include <memory>
#include "Screen.h"
#include "Enum.h"

class ScreenManager : public std::enable_shared_from_this<ScreenManager>
{
public:
  ScreenManager();

  void refresh();
  void handleInput();

  void switchWindow(AppScreen screenType);

private:
  std::unique_ptr<Screen> currentScreen;
};
