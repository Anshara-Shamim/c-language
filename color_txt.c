#include <stdio.h>
#include <windows.h>  // Windows-specific

int main() {
    // Set text color to green
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("Hello Green World!\n");

    // Set text color to red
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    printf("Hello Red World!\n");

    // Reset to default color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    return 0;
}
