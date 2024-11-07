#include "HomeScreen.h"

#include "Enum.h"

HomeScreen::HomeScreen(std::function<void(AppScreen)> switchScreenCallback) : Screen(switchScreenCallback), switchScreenCallback(switchScreenCallback)
{
}

HomeScreen::~HomeScreen()
{
  delwin(window);
}

void HomeScreen::refresh()
{
  wrefresh(window);
}

void HomeScreen::handleInput() {}
