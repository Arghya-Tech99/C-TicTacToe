#include<stdio.h>

int difficulty;
void input_difficulty();

int main() {
    input_difficulty();
}

void input_difficulty() {
    while (1) {
    printf("\nSelect difficulty level:");
    printf("\n1. Moderate");
    printf("\n2. Veteran");
    printf("\nEnter your choice: ");
    scanf("%d", &difficulty);

    if (difficulty != 1 && difficulty != 2) {
      printf("\nIncorrect choice enter (1/2)!!");
    } else {
      break;
    }
  };
}