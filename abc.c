#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define BUTTON_ID 1

int number;
int attempts = 0;
int score = 0;

HWND label, inputBox, scoreLabel;

// Function to check guess
void CheckGuess(HWND hwnd) {

    char buffer[100];
    char msg[150];

    GetWindowText(inputBox, buffer, 100);
    int guess = atoi(buffer);

    if (guess < 1 || guess > 10) {
        SetWindowText(label, "Enter number between 1 and 10");
        return;
    }

    attempts++;

    if (guess == number) {

        score++;  // increase score

        sprintf(msg, "Correct! You guessed in %d tries.", attempts);
        SetWindowText(label, msg);

        char scoreText[100];
        sprintf(scoreText, "Score: %d", score);
        SetWindowText(scoreLabel, scoreText);

        MessageBox(hwnd, "🎉 You guessed correctly!", "Success", MB_OK | MB_ICONINFORMATION);

        attempts = 0;
        number = rand() % 10 + 1;  // new number
    }
    else if (guess < number) {
        sprintf(msg, "Too Low! Attempts: %d", attempts);
        SetWindowText(label, msg);
    }
    else {
        sprintf(msg, "Too High! Attempts: %d", attempts);
        SetWindowText(label, msg);
    }

    SetWindowText(inputBox, "");
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    switch (uMsg) {

        case WM_CREATE:
            srand(time(NULL));
            number = rand() % 10 + 1;

            label = CreateWindow(
                "STATIC", "Guess a number between 1 and 10",
                WS_VISIBLE | WS_CHILD,
                20, 20, 300, 25,
                hwnd, NULL, NULL, NULL
            );

            inputBox = CreateWindow(
                "EDIT", "",
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
                20, 60, 200, 25,
                hwnd, NULL, NULL, NULL
            );

            CreateWindow(
                "BUTTON", "Guess",
                WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                20, 100, 200, 30,
                hwnd, (HMENU)BUTTON_ID, NULL, NULL
            );

            scoreLabel = CreateWindow(
                "STATIC", "Score: 0",
                WS_VISIBLE | WS_CHILD,
                20, 150, 200, 25,
                hwnd, NULL, NULL, NULL
            );
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) == BUTTON_ID) {
                CheckGuess(hwnd);
            }
            break;

        case WM_KEYDOWN:
            if (wParam == VK_RETURN) {
                CheckGuess(hwnd);
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

    const char CLASS_NAME[] = "GuessGame";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, "Guess Game (1-10)",
        WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 350, 250,
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
