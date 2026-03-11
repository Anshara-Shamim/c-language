// this is guess the number game!!
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int number, guess, attempts = 0;

    // Initialize random seed
    srand(time(NULL));

    // Random number between 1 and 10
    number = rand() % 10 + 1;

    printf("Welcome to Guess the Number! \n");
    printf("I'm thinking of a number between 1 and 10.\n");

    do {
        printf("Enter your guess: ");
        scanf("%d", &guess);
        attempts++;

        if (guess > number) {
            printf("Too high! Try again.\n");
        } else if (guess < number) {
            printf("Too low! Try again.\n");
        } else {
            printf("Congratulations! You guessed it in %d attempts.\n", attempts);
        }
    } while (guess != number);

    return 0;
}
