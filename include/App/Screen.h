#pragma once

class Screen
{
public:
  virtual ~Screen() = default;

  virtual void refresh() = 0;
  virtual void handleInput() = 0;
};
