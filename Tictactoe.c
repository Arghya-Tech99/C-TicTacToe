#include<stdio.h>
#include<stdlib.h>
#include <time.h>

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
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player);
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]);
void play_game();
void player_move(char board[BOARD_SIZE][BOARD_SIZE]);
void computer_move(char board[BOARD_SIZE][BOARD_SIZE]);
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);

int main() {
    srand(time(NULL));
    int choice;
    input_difficulty();
    
    do {
        play_game();
        printf("\n Want to play again?");
        printf("\n Press 1 for Yes and 0 for No");
        scanf("%d", &choice);
    } while(choice == 1);
    printf("\n Thanks for playing");
    
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

int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player) {
    // Checks if the player makes a horizontal line
    for (int i = 0; i < BOARD_SIZE; i++) {
    if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
      return 1; // Player wins - horizontally
    }

    if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
      return 1; // Player wins - vertically
    }
  }

  if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
      (board[2][0] == player && board[1][1] == player && board[0][2] == player)) {
    return 1; // Player wins - diagonally
  }
  return 0; // Player loses
}

int check_draw(char board[BOARD_SIZE][BOARD_SIZE]) {
    // check whether the grid is filled or not
    for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == ' ') {
        return 0;
      }
    }
  }
  return 1;
}

void play_game() {
  char board[BOARD_SIZE][BOARD_SIZE] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '},
  };
  char current_player = rand() % 2 == 0 ? X : O;

  print_board(board);
  while (1) {
    if (current_player == X) {
      player_move(board);
      print_board(board);
      if (check_win(board, X)) {
        score.player++;
        print_board(board);
        printf("Congratulation You have won.!!!");
        break;
      }
      current_player = O;
    } else {
      computer_move(board);
      print_board(board);
      if (check_win(board, O)) {
        score.computer++;
        print_board(board);
        printf("I won !!! But you played well...");
        break;
      }
      current_player = X;
    }

    if (check_draw(board)) {
      score.draw++;
      print_board(board);
      printf("\nIt's a draw!");
      break;
    }
  }
}

void player_move(char board[BOARD_SIZE][BOARD_SIZE]) {
   int count = 0, x, y;
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == ' ') {
        count++;
        x = i;
        y = j;
      }
    }
  }

  if (count == 1) {
    board[x][y] = X;
    return;
  }
  
  int row, col;
  do {
    printf("\nPlayer X's turn.");
    printf("\nEnter row and column (1-3) for X:");
    scanf("%d", &row);
    scanf("%d", &col);
    row--; col--; // converting to zero based
  } while (!is_valid_move(board, row, col));
  board[row][col] = X;
}

void computer_move(char board[BOARD_SIZE][BOARD_SIZE]) {
  // 1. Play for Immediate win
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == ' ') {
        board[i][j] = O;
        if (check_win(board, O)) {
          return;
        }
        board[i][j] = ' ';
      }
    }
  }

  // 2. Play for Immediate Block
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == ' ') {
        board[i][j] = X;
        if (check_win(board, X)) {
          board[i][j] = O;
          return;
        }
        board[i][j] = ' ';
      }
    }
  }

  // Veteran mode
  if (difficulty == 2) {
    // 3. Play Center if available
    if (board[1][1] == ' ') {
      board[1][1] = O;
      return;
    }

    // 4. Play Corner if available
    int corner[4][2] = {
      {0, 0},
      {0, 2},
      {2, 0},
      {2, 2}
    };
    for (int i = 0; i < 4; i++) {
      if (board[corner[i][0]][corner[i][1]] == ' ') {
        board[corner[i][0]][corner[i][1]] = O;
        return;
      }
    }
  }

  // 5. Play first available move
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == ' ') {
        board[i][j] = O;
        return;
      }
    }
  }
}


int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
  return !(row < 0 || col < 0 ||
           row > 2 || col > 2 ||
           board[row][col] != ' ');
}














