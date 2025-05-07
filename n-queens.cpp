#include <iostream>
using namespace std;

bool isSafe(int row, int col, int **board, int n) {
    // Check row and column
    for (int i = 0; i < n; i++) {
        if (board[row][i] == 1 || board[i][col] == 1) return false;
    }

    // Top-left diagonal
    int i = row, j = col;
    while (i >= 0 && j >= 0) {
        if (board[i][j] == 1) return false;
        i--; j--;
    }

    // Bottom-left diagonal
    i = row, j = col;
    while (i < n && j >= 0) {
        if (board[i][j] == 1) return false;
        i++; j--;
    }

    // Top-right diagonal
    i = row, j = col;
    while (i >= 0 && j < n) {
        if (board[i][j] == 1) return false;
        i--; j++;
    }

    // Bottom-right diagonal
    i = row, j = col;
    while (i < n && j < n) {
        if (board[i][j] == 1) return false;
        i++; j++;
    }

    return true;
}

bool solveNQueens(int **board, int col, int n) {
    if (col >= n) return true;

    for (int i = 0; i < n; i++) {
        if (isSafe(i, col, board, n)) {
            board[i][col] = 1;
            if (solveNQueens(board, col + 1, n)) return true;
            board[i][col] = 0; // Backtrack
        }
    }

    return false;
}

void printSolution(int **board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter the board size (n): ";
    cin >> n;

    // Allocate dynamic 2D array
    int** board = new int*[n];
    for (int i = 0; i < n; i++) {
        board[i] = new int[n];
    }

    // Initialize the board with 0s
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = 0;
        }
    }

    if (solveNQueens(board, 0, n)) {
        cout << "Solution exists:\n";
        printSolution(board, n);
    } else {
        cout << "No solution exists\n";
    }

    // Free memory
    for (int i = 0; i < n; i++) {
        delete[] board[i];
    }
    delete[] board;

    return 0;
}
