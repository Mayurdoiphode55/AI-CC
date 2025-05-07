#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

const int SIZE = 9;

int puzzle[SIZE][SIZE] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
};

int current[SIZE][SIZE];          // Working grid
bool isFixed[SIZE][SIZE];         // True if original (given) cell

int heuristic(int grid[SIZE][SIZE]) {
    int conflicts = 0;

    // Row conflicts
    for (int i = 0; i < SIZE; ++i) {
        vector<int> count(10, 0);
        for (int j = 0; j < SIZE; ++j) {
            count[grid[i][j]]++;
        }
        for (int k = 1; k <= 9; ++k) {
            if (count[k] > 1)
                conflicts += count[k] - 1;
        }
    }

    // Column conflicts
    for (int j = 0; j < SIZE; ++j) {
        vector<int> count(10, 0);
        for (int i = 0; i < SIZE; ++i) {
            count[grid[i][j]]++;
        }
        for (int k = 1; k <= 9; ++k) {
            if (count[k] > 1)
                conflicts += count[k] - 1;
        }
    }

    return conflicts;
}

void initialize() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            current[i][j] = puzzle[i][j];
            isFixed[i][j] = (puzzle[i][j] != 0);
        }
    }

    // Fill each 3x3 box randomly with remaining numbers
    for (int boxRow = 0; boxRow < 3; ++boxRow) {
        for (int boxCol = 0; boxCol < 3; ++boxCol) {
            vector<int> available;
            vector<pair<int, int> > emptyCells;
            bool used[10] = {false};

            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    int r = boxRow * 3 + i;
                    int c = boxCol * 3 + j;
                    int val = current[r][c];
                    if (val != 0)
                        used[val] = true;
                    else
                        emptyCells.push_back(make_pair(r, c));
                }
            }

            for (int n = 1; n <= 9; ++n) {
                if (!used[n]) available.push_back(n);
            }

            random_shuffle(available.begin(), available.end());

            for (size_t i = 0; i < emptyCells.size(); ++i) {
                current[emptyCells[i].first][emptyCells[i].second] = available[i];
            }
        }
    }
}

bool hillClimbStep() {
    int bestH = heuristic(current);
    bool improved = false;

    for (int boxRow = 0; boxRow < 3; ++boxRow) {
        for (int boxCol = 0; boxCol < 3; ++boxCol) {
            vector<pair<int, int> > mutableCells;

            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    int r = boxRow * 3 + i;
                    int c = boxCol * 3 + j;
                    if (!isFixed[r][c])
                        mutableCells.push_back(make_pair(r, c));
                }
            }

            for (size_t i = 0; i < mutableCells.size(); ++i) {
                for (size_t j = i + 1; j < mutableCells.size(); ++j) {
                    int r1 = mutableCells[i].first;
                    int c1 = mutableCells[i].second;
                    int r2 = mutableCells[j].first;
                    int c2 = mutableCells[j].second;

                    swap(current[r1][c1], current[r2][c2]);

                    int newH = heuristic(current);
                    if (newH < bestH) {
                        bestH = newH;
                        improved = true;
                    } else {
                        swap(current[r1][c1], current[r2][c2]); // undo
                    }
                }
            }
        }
    }

    return improved;
}

void printGrid(int grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    srand(time(0));
    initialize();

    int steps = 0;
    const int MAX_STEPS = 10000;

    while (heuristic(current) > 0 && steps < MAX_STEPS) {
        if (!hillClimbStep()) {
            cout << "Stuck in local minimum. Restarting...\n";
            initialize();
            steps = 0;
        } else {
            steps++;
        }
    }

    cout << "\nSolved Sudoku after " << steps << " steps:\n";
    printGrid(current);

    return 0;
}
