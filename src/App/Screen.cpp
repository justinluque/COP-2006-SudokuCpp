#include "Screen.h"

#include "Enum.h"

Screen::Screen(std::function<void(ScreenAction)> screenActionCallback) : screenActionCallback(screenActionCallback) {}
