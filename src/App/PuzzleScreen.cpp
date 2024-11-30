#include "PuzzleScreen.h"

#include <string>
#include <vector>
#include <utility>

#include "SudokuGenerator.h"
#include "SudokuSolver.h"
#include "Macro.h"
#include "Random.h"

// TODO: check entered nums (highlight bad ones as red and good as green)

PuzzleScreen::PuzzleScreen(std::function<void(ScreenAction)> screenActionCallback, PuzzleDifficulty difficulty) : Screen(screenActionCallback), difficulty(difficulty)
{
  // Clear previous screen
  clear();
  refresh();

  // Set the size of our main window
  sizeY = 17;
  sizeX = 70;

  // cellsize
  cellSize = 3;

  // grid start pos relative to main win
  gridStartY = 1;
  gridStartX = 2;

  // grid size
  gridSizeX = 32;
  gridSizeY = 13;

  // Help area size and start

  helpStartY = 2;
  helpStartX = gridStartX + gridSizeX + 2;

  helpSizeX = 30;
  helpSizeY = 13;

  // current cell starts at (4, 4)
  currentRow = 4;
  currentColumn = 4;

  messageDrawn = false;

  // Get screen dimensions
  int screenY = getmaxy(stdscr);
  int screenX = getmaxx(stdscr);

  // Calculate top-left corner coordinates to center the window
  int startY = (screenY - sizeY) / 2;
  int startX = (screenX - sizeX) / 2;

  window = newwin(sizeY, sizeX, startY, startX); // Full-screen window for resize prompt
  subHelpWindow = nullptr;

  keypad(window, true); /// Enable keypad inputs for our window

  switch (difficulty)
  {
  case PuzzleDifficulty::CUSTOM:
    currentPuzzle = SudokuGenerator::generateEmpty();
    break;

  case PuzzleDifficulty::EASY:
    currentPuzzle = SudokuGenerator::generateEasy();
    break;

  case PuzzleDifficulty::MEDIUM:
    currentPuzzle = SudokuGenerator::generateMedium();
    break;

  case PuzzleDifficulty::HARD:
    currentPuzzle = SudokuGenerator::generateHard();
    break;
  }

  if (difficulty != PuzzleDifficulty::CUSTOM)
    solvedPuzzle = SudokuSolver::solveBacktracking(currentPuzzle);

  drawGrid();

  drawHelp();

  drawSudokuNums();
}

PuzzleScreen::~PuzzleScreen()
{
  delwin(window);
}

void PuzzleScreen::refreshScreen()
{
  if (!messageDrawn)
    clearMessage();
  else
    messageDrawn = false;

  drawSudokuNums();
  wrefresh(window);
}

void PuzzleScreen::handleInput()
{
  int key = wgetch(window);

  switch (key)
  {
  case KEY_UP:
    currentRow = (currentRow + 8) % 9;
    break;

  case KEY_DOWN:
    currentRow = (currentRow + 1) % 9;
    break;

  case KEY_LEFT:
    currentColumn = (currentColumn + 8) % 9;
    break;

  case KEY_RIGHT:
    currentColumn = (currentColumn + 1) % 9;
    break;

  case CTRL_X:
  case 'x':
    screenActionCallback(ScreenAction::QUIT);
    break;

  case 's':
  {
    showSolution();
    break;
  }

  case 'h':
  {
    showHint();
    break;
  }

  case 'r':
    currentPuzzle->resetToFixedCells();
    break;

  case 'm':
    screenActionCallback(ScreenAction::MAIN_MENU);
    break;

  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    currentPuzzle->setCellValue(key - '0', currentRow, currentColumn);

    if (SudokuSolver::isSolved(currentPuzzle))
    {
      drawMessage("You've solved the puzzle! Well done!");
      currentPuzzle->lockPuzzle();
    }

    else if (currentPuzzle->getFixed(currentRow, currentColumn))
    {
      drawMessage("You can't edit this clue as it's fixed.");
    }

    break;

  case KEY_BACKSPACE:
    currentPuzzle->setCellValue(0, currentRow, currentColumn);
    break;
  }
}

void PuzzleScreen::showHint()
{
  std::vector<std::pair<int, int>> candidates;

  for (int row = 0; row < 9; row++)
    for (int col = 0; col < 9; col++)
    {
      int cellValue = currentPuzzle->getCellValue(row, col);
      bool isCellEditable = !currentPuzzle->getFixed(row, col);
      bool isCellEmpty = (cellValue == 0);
      bool isPlacementValid = SudokuSolver::isCorrectPlacement(currentPuzzle, cellValue, row, col);

      if (isCellEditable && (isCellEmpty || !isPlacementValid))
      {
        candidates.push_back(std::make_pair(row, col));
      }
    }

  if (candidates.empty())
  {
    drawMessage("No cells can receive a hint.");
    return;
  }

  std::pair<int, int> chosenCell = Random::choose(candidates);

  if (solvedPuzzle == nullptr)
    findSolution();

  currentColumn = chosenCell.second;
  currentRow = chosenCell.first;

  int solvedCellValue = solvedPuzzle->getCellValue(currentRow, currentColumn);

  currentPuzzle->setFixedCellValue(solvedCellValue, currentRow, currentColumn);

  return;
}

void PuzzleScreen::findSolution()
{
  if (currentPuzzle->getTotalClues() < 17)
    drawMessage("Multiple solutions found; using the first one identified");

  if (!SudokuSolver::isValid(currentPuzzle))
  {
    drawMessage("Puzzle could not be solved. Try resetting the puzzle.");
    return;
  }

  if (SudokuSolver::isSolved(currentPuzzle))
  {
    drawMessage("Puzzle is already complete!");
    return;
  }

  std::unique_ptr<SudokuPuzzle> copiedPuzzle = std::make_unique<SudokuPuzzle>(*currentPuzzle);

  if (difficulty != PuzzleDifficulty::CUSTOM)
    copiedPuzzle->resetToFixedCells();

  solvedPuzzle = SudokuSolver::solveBacktracking(copiedPuzzle);

  if (solvedPuzzle == nullptr)
  {
    drawMessage("Puzzle could not be solved.");
    return;
  }
}

void PuzzleScreen::showSolution()
{
  if (solvedPuzzle == nullptr)
    findSolution();

  currentPuzzle = std::move(solvedPuzzle);

  currentPuzzle->lockPuzzle();
}

void PuzzleScreen::drawGrid()
{
  int rowsDrawn = 0, colsDrawn = 0;
  for (int row = 0; row <= 9; row++)
  {
    for (int column = 0; column <= 9; column++)
    {
      if (column % 3 == 0 && row != 0)
      {
        mvwprintw(window, rowsDrawn + gridStartY, colsDrawn + gridStartX, "|");
        colsDrawn++;
      }
      colsDrawn += cellSize;
    }
    rowsDrawn++;
    colsDrawn = 0;
    if (row % 3 == 0)
    {
      mvwprintw(window, rowsDrawn + gridStartY, colsDrawn + gridStartX, "+---------+---------+---------+");
      rowsDrawn++;
    }
  }
}

void PuzzleScreen::drawNumByPos(int num, int row, int col)
{
  int trueRow = (row / 3 + 2) + row + gridStartY;
  int trueCol = col / 3 + 2 + col * 3 + gridStartX;

  if (row == currentRow && col == currentColumn)
    highlightOn(HIGHLIGHT_COLOR_PAIR);
  if (num == 0)
    mvwprintw(window, trueRow, trueCol, "-");
  else
    mvwprintw(window, trueRow, trueCol, "%d", num);
  if (row == currentRow && col == currentColumn)
    highlightOff(HIGHLIGHT_COLOR_PAIR);
}

void PuzzleScreen::drawSudokuNums()
{
  box(window, 0, 0);

  for (int row = 0; row < 9; row++)
  {
    for (int col = 0; col < 9; col++)
    {
      int cellValue = currentPuzzle->getCellValue(row, col);
      drawNumByPos(cellValue, row, col);
    }
  }
}

void PuzzleScreen::drawHelp()
{
  if (subHelpWindow == nullptr)
  {
    subHelpWindow = derwin(window, helpSizeY, helpSizeX, helpStartY, helpStartX);
  }
  box(subHelpWindow, 0, 0);

  std::string title = "Controls";

  std::string Navigation = "Navigate using arrow keys";
  std::string sMsg = "[s] - Solve puzzle        ";
  std::string hMsg = "[h] - Give hint           ";
  std::string cMsg = "[v] - Validate guesses    ";
  std::string rMsg = "[r] - Reset the puzzle    ";
  std::string mMsg = "[m] - Main Menu           ";
  std::string xMsg = "[x] - Exit                ";

  mvwprintw(subHelpWindow, 1, (helpSizeX - title.size()) / 2, title.data());
  mvwprintw(subHelpWindow, 3, (helpSizeX - Navigation.size()) / 2, Navigation.data());
  mvwprintw(subHelpWindow, 5, (helpSizeX - sMsg.size()) / 2, sMsg.data());
  mvwprintw(subHelpWindow, 6, (helpSizeX - hMsg.size()) / 2, hMsg.data());
  mvwprintw(subHelpWindow, 7, (helpSizeX - cMsg.size()) / 2, cMsg.data());
  mvwprintw(subHelpWindow, 8, (helpSizeX - rMsg.size()) / 2, rMsg.data());
  mvwprintw(subHelpWindow, 9, (helpSizeX - mMsg.size()) / 2, mMsg.data());
  mvwprintw(subHelpWindow, 10, (helpSizeX - xMsg.size()) / 2, xMsg.data());

  wrefresh(subHelpWindow);
}

void PuzzleScreen::drawMessage(std::string msg)
{
  clearMessage();
  mvwprintw(window, 15, 1, msg.c_str());
  messageDrawn = true;
}

void PuzzleScreen::clearMessage()
{
  mvwprintw(window, 15, 1, "                                                                    ");
}

void PuzzleScreen::highlightOn(int highlight_color_pair_code)
{
  wattr_on(window, COLOR_PAIR(highlight_color_pair_code), 0);
}

void PuzzleScreen::highlightOff(int highlight_color_pair_code)
{
  wattr_off(window, COLOR_PAIR(highlight_color_pair_code), 0);
}
