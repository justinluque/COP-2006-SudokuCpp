#pragma once

#include "Screen.h"

class HomeScreen : public Screen
{
public:
  HomeScreen();
  ~HomeScreen();

  void refresh() override;
  void handleInput() override;
};
