/*
    Mini Game Project: Tic Tac Toe
    --------------------------------
    Demonstrates:
      - Loops (for, while)
      - Arrays (2D board)
      - Conditional logic (if/else, switch)
    Features:
      - Dynamic board display after each move
      - Win/loss/draw detection
      - Replay option
*/

#include <iostream>
using namespace std;

const int SIZE = 3;

// Function to display the board dynamically
void displayBoard(char board[SIZE][SIZE]) {
    cout << "\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << " " << board[i][j];
            if (j < SIZE - 1) cout << " |";
        }
        cout << "\n";
        if (i < SIZE - 1) cout << "---|---|---\n";
    }
    cout << "\n";
}

// Function to initialize the board with empty cells (numbered 1-9 for guidance)
void initBoard(char board[SIZE][SIZE]) {
    int num = 1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '0' + num; // store as char digit placeholder
            num++;
        }
    }
}

// Convert player's move number (1-9) into row/col
bool placeMove(char board[SIZE][SIZE], int choice, char playerSymbol) {
    if (choice < 1 || choice > 9) return false;

    int row = (choice - 1) / SIZE;
    int col = (choice - 1) % SIZE;

    // Check if the cell is already taken (i.e., not a digit anymore)
    if (board[row][col] == 'X' || board[row][col] == 'O') {
        return false; // invalid move, cell occupied
    }

    board[row][col] = playerSymbol;
    return true;
}

// Check rows, columns, and diagonals for a win
bool checkWin(char board[SIZE][SIZE], char playerSymbol) {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == playerSymbol && board[i][1] == playerSymbol && board[i][2] == playerSymbol)
            return true;
        if (board[0][i] == playerSymbol && board[1][i] == playerSymbol && board[2][i] == playerSymbol)
            return true;
    }
    // Check diagonals
    if (board[0][0] == playerSymbol && board[1][1] == playerSymbol && board[2][2] == playerSymbol)
        return true;
    if (board[0][2] == playerSymbol && board[1][1] == playerSymbol && board[2][0] == playerSymbol)
        return true;

    return false;
}

// Check if the board is full (draw condition)
bool isBoardFull(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false; // empty cell still exists
            }
        }
    }
    return true;
}

// Main game loop for a single round
void playGame() {
    char board[SIZE][SIZE];
    initBoard(board);

    char currentPlayer = 'X';
    int choice;
    bool gameOver = false;

    cout << "\n=== TIC TAC TOE ===\n";
    cout << "Player 1: X    Player 2: O\n";
    cout << "Enter a number 1-9 to place your mark:\n";
    displayBoard(board);

    while (!gameOver) {
        cout << "Player " << currentPlayer << ", enter your move (1-9): ";
        cin >> choice;

        // Input validation loop
        while (cin.fail() || !placeMove(board, choice, currentPlayer)) {
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cout << "Invalid move. Try again (1-9, cell must be empty): ";
            cin >> choice;
        }

        displayBoard(board);

        if (checkWin(board, currentPlayer)) {
            cout << "*** Player " << currentPlayer << " WINS! ***\n";
            gameOver = true;
        } else if (isBoardFull(board)) {
            cout << "*** It's a DRAW! ***\n";
            gameOver = true;
        } else {
            // Switch turns
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
}

int main() {
    char playAgain;

    do {
        playGame();

        cout << "\nPlay again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "\nThanks for playing! Goodbye.\n";
    return 0;
}
