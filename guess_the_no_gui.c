#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define BUTTON_ID 1

int number;
int attempts = 0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    static HWND label;
    static HWND inputBox;

    switch (uMsg) {

        case WM_CREATE:
            srand(time(NULL));
            number = rand() % 10 + 1;   // Random number between 1 and 10

            // Instruction label
            label = CreateWindow(
                "STATIC", "Guess a number between 1 and 10",
                WS_VISIBLE | WS_CHILD,
                20, 20, 300, 25,
                hwnd, NULL, NULL, NULL
            );

            // Input box
            inputBox = CreateWindow(
                "EDIT", "",
                WS_VISIBLE | WS_CHILD | WS_BORDER,
                20, 60, 200, 25,
                hwnd, NULL, NULL, NULL
            );

            // Guess button
            CreateWindow(
                "BUTTON", "Guess",
                WS_VISIBLE | WS_CHILD,
                20, 100, 200, 30,
                hwnd, (HMENU)BUTTON_ID, NULL, NULL
            );
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) == BUTTON_ID) {

                char buffer[100];
                char msg[150];

                GetWindowText(inputBox, buffer, 100);
                int guess = atoi(buffer);

                // Validate range
                if (guess < 1 || guess > 10) {
                    SetWindowText(label, "❗ Enter a number between 1 and 10");
                    break;
                }

                attempts++;

                if (guess == number) {
                    sprintf(msg, "🎉 Correct! You guessed in %d tries. New number generated!", attempts);
                    attempts = 0;
                    number = rand() % 10 + 1;  // new number
                }
                else if (guess < number) {
                    sprintf(msg, "Too low! Attempts: %d", attempts);
                }
                else {
                    sprintf(msg, "Too high! Attempts: %d", attempts);
                }

                SetWindowText(label, msg);
                SetWindowText(inputBox, "");   // Clear input box
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

    const char CLASS_NAME[] = "GuessNumberWindowClass";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, "Guess the Number (1-10)",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 250,
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
