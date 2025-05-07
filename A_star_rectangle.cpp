#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;

// Room dimensions
const int ROOM_WIDTH = 10;
const int ROOM_HEIGHT = 10;

// Object struct
struct Object {
    int width, height;
    string name;
};

// State of the room
struct State {
    vector<vector<int>> roomGrid;  // 0 = empty, 1 = occupied
    int objIndex;  // index of next object to place
    int g;         // cost so far = number of placed objects
    int h;         // heuristic = remaining empty area
    vector<Object> placedObjects;

    // For priority queue: smaller total cost = higher priority
    bool operator<(const State &s) const {
        return (g + h) > (s.g + s.h);
    }
};

// Check if we can place object at (x, y)
bool canPlace(const vector<vector<int>> &grid, int x, int y, int w, int h) {
    if (x + h > ROOM_HEIGHT || y + w > ROOM_WIDTH) return false;
    for (int i = x; i < x + h; i++)
        for (int j = y; j < y + w; j++)
            if (grid[i][j] != 0)
                return false;
    return true;
}

// Place object in room grid
void placeObject(vector<vector<int>> &grid, int x, int y, int w, int h) {
    for (int i = x; i < x + h; i++)
        for (int j = y; j < y + w; j++)
            grid[i][j] = 1;
}

// Heuristic: empty cells
int calculateHeuristic(const vector<vector<int>> &grid) {
    int empty = 0;
    for (auto &row : grid)
        for (int cell : row)
            if (cell == 0) empty++;
    return empty;
}

// Print room
void printRoom(const vector<vector<int>> &grid) {
    cout << "\nRoom Layout (1 = filled):\n";
    for (auto &row : grid) {
        for (int cell : row)
            cout << (cell ? "#" : ".") << " ";
        cout << endl;
    }
}

// Main A* search
void AStarRoomArrangement(vector<Object> objects) {
    priority_queue<State> pq;

    State initial;
    initial.roomGrid = vector<vector<int>>(ROOM_HEIGHT, vector<int>(ROOM_WIDTH, 0));
    initial.objIndex = 0;
    initial.g = 0;
    initial.h = calculateHeuristic(initial.roomGrid);
    pq.push(initial);

    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();

        if (curr.objIndex == objects.size()) {
            cout << "\n✅ All objects placed successfully!";
            printRoom(curr.roomGrid);
            return;
        }

        Object obj = objects[curr.objIndex];

        // Try placing at every position
        for (int i = 0; i < ROOM_HEIGHT; i++) {
            for (int j = 0; j < ROOM_WIDTH; j++) {
                if (canPlace(curr.roomGrid, i, j, obj.width, obj.height)) {
                    State newState = curr;
                    placeObject(newState.roomGrid, i, j, obj.width, obj.height);
                    newState.objIndex++;
                    newState.g++;
                    newState.h = calculateHeuristic(newState.roomGrid);
                    newState.placedObjects.push_back(obj);
                    pq.push(newState);
                }
            }
        }
    }

    cout << "\n❌ Failed to place all objects efficiently.";
}

int main() {
    // Define objects
    vector<Object> objects = {
        {2, 4, "Rect1"}, {1, 5, "Rect2"}, {2, 3, "Rect3"}, {1, 4, "Rect4"}, {3, 2, "Rect5"},
        {2, 2, "Square1"}, {3, 3, "Square2"}, {1, 1, "Square3"}, {2, 2, "Square4"}
    };

    cout << "📦 Starting A* Room Arrangement...\n";
    AStarRoomArrangement(objects);

    return 0;
}
