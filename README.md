# Requirements

- C++ Compiler with C++20 support
- Ncurses library and headers
- Windows or MacOS
- A terminal with color support

# Building

## Windows

To compile the project on Windows, you will need build tools that give you access to Ncurses and its headers as well as an update version of gcc. The easiest way to get access to these, in my opinion was through [MSYS2](https://www.msys2.org/) though there are most likely other ways as well. If you are attempting to compile this project using the Makefile on a toolchain other than UCRT64 MSYS2, you will most likely have to alter the Makefile, specifically the include directories of CXXFLAGS in Makefile.win.

1. Install [MSYS2](https://www.msys2.org/) (The Windows Makefile is set up for specifically the UCRT64 environment)
2. Install dependencies
```
pacamn -S ncurses-devel ncurses base-devel make mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-make
```
3. Clone the repository
```
git clone https://github.com/justinluque/COP-2006-SudokuCpp SudokuCpp/
cd SudokuCpp/
```
4. Compile
```
make
```

If all goes well, an executable `Sudoku.exe` will be placed in the current directory.

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
