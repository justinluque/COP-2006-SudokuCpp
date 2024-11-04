#pragma once

#include "Screen.h"

class PuzzleScreen : public Screen
{
public:
  PuzzleScreen();
  ~PuzzleScreen();

  void refresh() override;
  void handleInput() override;
};
