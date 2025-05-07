#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <stack>
using namespace std;

struct Node {
    int x, y;
    int g, h;
    Node* parent;

    Node(int x, int y, int g, int h, Node* p = nullptr)
        : x(x), y(y), g(g), h(h), parent(p) {}

    int f() const { return g + h; }

    bool operator>(const Node& other) const {
        return f() > other.f();
    }
};

// Heuristic: Manhattan distance
int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

bool isValid(int x, int y, int rows, int cols, vector<vector<int>>& grid) {
    return x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 0;
}

void printPath(Node* node) {
    stack<pair<int, int>> path;
    while (node != nullptr) {
        path.push({node->x, node->y});
        node = node->parent;
    }
    cout << "Path: ";
    while (!path.empty()) {
        cout << "(" << path.top().first << "," << path.top().second << ") ";
        path.pop();
    }
    cout << endl;
}

void aStarSearch(vector<vector<int>>& grid, pair<int, int> start, pair<int, int> end) {
    int rows = grid.size(), cols = grid[0].size();

    priority_queue<Node*, vector<Node*>, function<bool(Node*, Node*)>> open(
        [](Node* a, Node* b) { return *a > *b; });

    vector<vector<bool>> closed(rows, vector<bool>(cols, false));

    Node* startNode = new Node(start.first, start.second, 0,
                               heuristic(start.first, start.second, end.first, end.second));

    open.push(startNode);

    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    while (!open.empty()) {
        Node* current = open.top();
        open.pop();

        if (closed[current->x][current->y])
            continue;

        closed[current->x][current->y] = true;

        if (current->x == end.first && current->y == end.second) {
            printPath(current);
            return;
        }

        for (int i = 0; i < 4; i++) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if (isValid(nx, ny, rows, cols, grid) && !closed[nx][ny]) {
                int newG = current->g + 1;
                int newH = heuristic(nx, ny, end.first, end.second);
                Node* neighbor = new Node(nx, ny, newG, newH, current);
                open.push(neighbor);
            }
        }
    }

    cout << "No path found." << endl;
}

int main() {
    int rows, cols;
    cout << "Enter grid size (rows cols): ";
    cin >> rows >> cols;

    vector<vector<int>> grid(rows, vector<int>(cols, 0));

    int obstacles;
    cout << "Enter number of obstacles: ";
    cin >> obstacles;
    cout << "Enter obstacle coordinates (row col):" << endl;
    for (int i = 0; i < obstacles; i++) {
        int r, c;
        cin >> r >> c;
        grid[r][c] = 1;
    }

    pair<int, int> start, end;
    cout << "Enter start position (row col): ";
    cin >> start.first >> start.second;

    cout << "Enter end position (row col): ";
    cin >> end.first >> end.second;

    cout << "Finding path using A* Algorithm..." << endl;
    aStarSearch(grid, start, end);

    return 0;
}
