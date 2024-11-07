#include "Screen.h"

#include "Enum.h"

Screen::Screen(std::function<void(AppScreen)> switchScreenCallback) : switchScreenCallback(switchScreenCallback) {}
