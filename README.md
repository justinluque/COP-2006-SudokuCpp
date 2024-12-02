# Requirements

- C++ Compiler with C++20 support
- Ncurses library and headers
- Windows or MacOS
- A terminal with color support

# References

- https://www.eso.org/~ndelmott/ascii.html

  Used to define ascii codes for ctrl characters

- https://github.com/msys2/MINGW-packages/issues/10312#issuecomment-1641416187

  -DNCURSES_STATIC flag forces static linking which fixes compilation for MSYS2 toolchains 

- https://www.youtube.com/watch?v=3YiPdibiQHA

  Used to create a menu TUI system with ncurses

- https://www.youtube.com/watch?v=TjFXEUCMqI8

  Cool one pass solution to checking whether a sudoku puzzle is valid

- https://www.nature.com/articles/nature.2012.9751

  Generally, a valid sudoku puzzle with a unique solution must have at least 17 clues
