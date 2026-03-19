# C Programs Collection

A collection of beginner-to-intermediate C programs demonstrating console I/O, Windows GUI development using the Win32 API, and system-level features like timers and colored output.

---

## Libraries Used

### `<stdio.h>` — Standard Input/Output
Used for `printf`, `scanf`, `sprintf`.
- `printf()` — print formatted text to console
- `scanf()` — read user input from console
- `sprintf()` — write formatted string into a buffer

### `<stdlib.h>` — Standard Library
Used for `atoi`, `rand`, `srand`.
- `atoi()` — convert string to integer
- `rand()` — generate a pseudo-random number
- `srand()` — seed the random number generator

### `<time.h>` — Time Functions
Used for `time`, `clock`.
- `time(NULL)` — get current time (used to seed `srand`)
- `clock()` — measure elapsed CPU time (used in stopwatch)
- `CLOCKS_PER_SEC` — constant to convert clock ticks to seconds

### `<windows.h>` — Windows API (Win32)
Required for all GUI programs and the colored console program.

#### Window & Message Functions
- `CreateWindow()` / `CreateWindowEx()` — create windows, buttons, labels, input boxes
- `ShowWindow()` — display a window
- `RegisterClass()` — register a custom window class
- `DefWindowProc()` — default message handler
- `GetMessage()` / `TranslateMessage()` / `DispatchMessage()` — the main message loop
- `PostQuitMessage()` — signal the application to exit

#### Control & UI Functions
- `SetWindowText()` — update text of a label, button, or input field
- `GetWindowText()` — read text from an input field
- `MessageBox()` — show a pop-up dialog box

#### Timer Functions
- `SetTimer()` — fire `WM_TIMER` messages at regular intervals (used in stopwatch)

#### Console Color Functions
- `GetStdHandle(STD_OUTPUT_HANDLE)` — get the console output handle
- `SetConsoleTextAttribute()` — change text/background color in console

#### Common Win32 Constants Used
| Constant | Meaning |
|----------|---------|
| `WM_CREATE` | Window is being created |
| `WM_COMMAND` | Button or menu item clicked |
| `WM_TIMER` | Timer interval elapsed |
| `WM_KEYDOWN` | Keyboard key pressed |
| `WM_DESTROY` | Window is being closed |
| `WS_VISIBLE` | Control is visible |
| `WS_CHILD` | Control is a child of another window |
| `WS_BORDER` | Draw a border around control |
| `MB_OK` | MessageBox with OK button |
| `VK_RETURN` | Virtual key code for Enter key |

---

## How to Compile & Run

### Requirements
- **Compiler:** GCC with MinGW (on Windows) or MSVC
- **OS:** Windows (required for all programs using `<windows.h>`)

### Install MinGW (if not installed)
Download from [https://www.mingw-w64.org](https://www.mingw-w64.org) and add `bin/` to your system PATH.

---

## Compiler Flag Reference

| Flag | Purpose |
|------|---------|
| `-o filename.exe` | Set the output executable name |
| `-mwindows` | Required for Win32 GUI apps — links the Windows subsystem and suppresses the console window |

> **Note:** If you compile a GUI program **without** `-mwindows`, a black console window will appear behind your GUI. Always use `-mwindows` for Win32 GUI applications.

---



