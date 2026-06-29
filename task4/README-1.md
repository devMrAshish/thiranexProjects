# Mini Game Project: Tic Tac Toe

A console-based Tic Tac Toe game written in C++. Built to demonstrate core programming concepts — loops, arrays, and conditional logic — through a simple, interactive 2-player game.

## Objective

Create a console-based mini game in C++ that demonstrates core programming concepts such as loops, arrays, and conditional logic.

## Key Features

- Uses loops, arrays, and conditional statements to drive the game logic
- Displays the game board dynamically after each move
- Detects wins, losses, and draws
- Lets players replay without restarting the program

## How to Compile and Run

```bash
g++ tic_tac_toe.cpp -o tic_tac_toe
./tic_tac_toe
```

On Windows (with MinGW):

```bash
g++ tic_tac_toe.cpp -o tic_tac_toe.exe
tic_tac_toe.exe
```

## How to Play

1. The board is numbered 1–9, left to right, top to bottom:

   ```
    1 | 2 | 3
   ---+---+---
    4 | 5 | 6
   ---+---+---
    7 | 8 | 9
   ```

2. Player 1 is `X`, Player 2 is `O`. Players take turns.
3. On your turn, type the number of the cell you want to mark and press Enter.
4. The board reprints after every move so you can see the updated state.
5. The game announces a winner as soon as three marks line up in a row, column, or diagonal — or announces a draw if the board fills up first.
6. After the game ends, you'll be asked **"Play again? (y/n)"**. Enter `y` to start a new round or `n` to exit.

## Concepts Demonstrated

| Concept | Where it's used |
|---|---|
| **2D Arrays** | `char board[3][3]` stores the game state |
| **Loops** | Board display, input validation, and the replay loop (`do...while`) |
| **Conditional Logic** | Move validation, win/draw detection, turn switching |
| **Functions** | Code is broken into `displayBoard`, `placeMove`, `checkWin`, `isBoardFull`, and `playGame` for clarity |

## Expected Outcome

An interactive game with dynamic board display, win/loss detection, and replay functionality, showcasing effective implementation of game logic.

## File

- `tic_tac_toe.cpp` — full source code, single file, no external dependencies
