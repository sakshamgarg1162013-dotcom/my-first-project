# Copilot Instructions for This Codebase

## Overview
This repository contains C projects, primarily simple console games such as Snake and Tic-Tac-Toe. The code is organized by project, with each game in its own C source file under the `projects in c/` directory. Example files:
- `projects in c/snake.c`: Snake game implementation
- `projects in c/tictactoe.c`: Tic-Tac-Toe game implementation

## Key Patterns & Conventions
- **Platform-Specific Code:**
  - Uses `#ifdef _WIN32` to distinguish between Windows and other platforms for actions like clearing the screen.
  - Windows-specific headers (`<windows.h>`) and functions (e.g., `SetConsoleMode`, `GetStdHandle`) are used for terminal control.
- **Terminal Handling:**
  - Functions like `disable_echo_and_icanon` and `restore_terminal` manage console input modes for better game input handling.
  - Always call `restore_terminal` on exit to reset terminal state (registered via `atexit`).
- **No External Build System:**
  - Build each game manually using a C compiler. Example (from project root):
    ```sh
    gcc "projects in c/snake.c" -o "projects in c/snake.exe" -luser32
    ```
  - Adjust library flags as needed for Windows (e.g., `-luser32` for some console functions).
- **No Automated Tests:**
  - There are no test scripts or frameworks present. Manual play-testing is the primary validation method.
- **No Project-Wide Header Files:**
  - Each `.c` file is self-contained, with all necessary includes and definitions.

## Developer Workflows
- **Build:**
  - Use `gcc` or another C compiler. Output executables are placed alongside source files.
- **Run:**
  - Run the resulting `.exe` files directly in the terminal or via double-click in Windows.
- **Debug:**
  - Use print statements or a debugger like `gdb` (if available for Windows).

## File/Directory Reference
- `projects in c/`: Main directory for C game projects.
- `snake.c`, `tictactoe.c`: Example game source files.
- No central `main.c` or shared library code.

## Example: Adding a New Game
1. Create a new `.c` file in `projects in c/`.
2. Follow the pattern of existing files: include necessary headers, implement `main`, handle terminal modes if needed.
3. Build with `gcc` as above.

---

**Note:** This project is Windows-focused. For cross-platform support, always use `#ifdef _WIN32` guards for OS-specific code.
