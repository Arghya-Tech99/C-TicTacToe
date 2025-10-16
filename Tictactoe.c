#include<stdio.h>
#include<stdlib.h>

// Macros define for this project
# define BOARD_SIZE 3
#define X 'X'
#define O 'O'

// Defining a structure and initializing its member values
typedef struct {
  int player; // Player score
  int computer; // Computer score
  int draw; // Draw matches
} Score; 
Score score = {.player = 0, .computer = 0, .draw = 0};

int difficulty;
void input_difficulty();
void clear_screen();
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);

int main() {
    input_difficulty();
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {' ', ' ', ' '},
        {'X', ' ', 'X'},
        {' ', 'O', ' '},
    };
    print_board(board);
}

void input_difficulty() {
    while (1) {
    printf("\nSelect difficulty level:");
    printf("\n1. Moderate");
    printf("\n2. Veteran");
    printf("\nEnter your choice: ");
    scanf("%d", &difficulty);

    if (difficulty != 1 && difficulty != 2) {
      printf("\nIncorrect choice !!");
    } else {
      break;
    }
  };
}

void clear_screen() {
    system("cls");
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
  clear_screen();
  printf("Score - Player X: %d, Computer: %d, Draws: %d", score.player, score.computer, score.draw);
  printf("\nTic-Tac-Toe\n");

  for (int i = 0 ; i < BOARD_SIZE; i++) {
    printf("\n");
    for (int j = 0; j < BOARD_SIZE; j++) {
      printf(" %c ", board[i][j]);
      if (j < BOARD_SIZE - 1) {
        printf("|");
      }
    }
    if (i < BOARD_SIZE - 1) {
      printf("\n---+---+---");
    }
  }
  printf("\n\n");
}