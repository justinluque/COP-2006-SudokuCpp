#pragma once

class Screen
{
public:
  virtual ~Screen() = default;

  virtual void refresh();
  virtual void handleInput();
};
