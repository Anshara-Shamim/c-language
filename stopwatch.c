#include <windows.h>
#include <stdio.h>
#include <time.h>

#define BUTTON_START 1
#define BUTTON_STOP  2
#define BUTTON_RESET 3

int running = 0;
clock_t startTime = 0;
double elapsed = 0.0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND label;

    switch (uMsg) {
        case WM_CREATE:
            // Timer display label
            label = CreateWindow(
                "STATIC", "00:00:00",
                WS_VISIBLE | WS_CHILD,
                50, 20, 200, 50,
                hwnd, NULL, NULL, NULL
            );

            // Start button
            CreateWindow("BUTTON", "Start",
                         WS_VISIBLE | WS_CHILD,
                         20, 100, 80, 30,
                         hwnd, (HMENU)BUTTON_START, NULL, NULL);

            // Stop button
            CreateWindow("BUTTON", "Stop",
                         WS_VISIBLE | WS_CHILD,
                         120, 100, 80, 30,
                         hwnd, (HMENU)BUTTON_STOP, NULL, NULL);

            // Reset button
            CreateWindow("BUTTON", "Reset",
                         WS_VISIBLE | WS_CHILD,
                         220, 100, 80, 30,
                         hwnd, (HMENU)BUTTON_RESET, NULL, NULL);

            // Set a timer to update every 100ms
            SetTimer(hwnd, 1, 100, NULL);
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case BUTTON_START:
                    if (!running) {
                        startTime = clock() - (clock_t)(elapsed * CLOCKS_PER_SEC);
                        running = 1;
                    }
                    break;
                case BUTTON_STOP:
                    if (running) {
                        elapsed = (double)(clock() - startTime) / CLOCKS_PER_SEC;
                        running = 0;
                    }
                    break;
                case BUTTON_RESET:
                    running = 0;
                    elapsed = 0;
                    SetWindowText(label, "00:00:00");
                    break;
            }
            break;

        case WM_TIMER:
            if (running) {
                elapsed = (double)(clock() - startTime) / CLOCKS_PER_SEC;
                int hours = (int)elapsed / 3600;
                int minutes = ((int)elapsed % 3600) / 60;
                int seconds = (int)elapsed % 60;

                char buffer[50];
                sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);
                SetWindowText(label, buffer);
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nShowCmd) {

    const char CLASS_NAME[] = "StopwatchWindowClass";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, "Simple Stopwatch",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 350, 200,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, nShowCmd);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
