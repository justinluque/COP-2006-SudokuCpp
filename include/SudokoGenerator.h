#pragma once

#include <memory>
#include "SudokoPuzzle.h"

class SudokoGenerator
{
public:
  SudokoGenerator() = delete;

  static std::unique_ptr<SudokoPuzzle> generateEasy();

  static std::unique_ptr<SudokoPuzzle> generateMedium();

  static std::unique_ptr<SudokoPuzzle> generateHard();
};