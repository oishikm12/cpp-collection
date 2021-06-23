#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void replaceColor(vector<vector<int>> &, int, int, int);

int main() {
    /**
     * In order to convert all connected same colors in a graph to another, 
     * we will use BFS to traverse to each node, and then check with all
     * of its neighbours to confirm if they are of the same color and need
     * to be converted or not
     */
    cout << "\nThis program is used to replace connected elements resembling a certain element in a grid.\n" << endl; 
    int size;
    cout << "Enter the size of the grid to consider: ";
    cin >> size;

    vector<vector<int>> grid(size, vector<int>(size));
    cout << "Enter space seperated elements of the grid representing colours," << endl;
    for (int i = 0; i < size; i += 1) for (int j = 0; j < size; j += 1) cin >> grid[i][j];

    int col, x, y;
    cout << "\nEnter the color to replace replace: ";
    cin >> col;
    cout << "Enter space seperated coordinates to start replacing from," << endl;
    cin >> x >> y;

    int oldCol = grid[x][y];
    replaceColor(grid, col, x, y);

    cout << "\nThe grid after replacing all " << oldCol << " with " << col << " is," << endl;
    for (int i = 0; i < size; i += 1) {
        for (int j = 0; j < size; j += 1) {
            cout << grid[i][j];
            if (j != size - 1) cout << " ";
        }
        cout << endl;
    }

    cout << endl;

    return 0;
}

void replaceColor(vector<vector<int>> &grid, int newColor, int xCord, int yCord) {
    int n = grid.size();

    // We use this to keep track of all visited nodes
    vector<vector<bool>> visited(n, vector<bool>(n, false));

    // Since we want to visit all neighbours of a node before
    // others we use a queue to keep track of convertable nodes
    queue<pair<int, int>> store;
    store.push(make_pair(xCord, yCord));
    visited[xCord][yCord] = true;

    // This represents all movable directions in the graph
    vector<pair<int, int>> options = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    // This is the color to be replaced with new color
    int oldCol = grid[xCord][yCord];

    while (!store.empty()) {
        auto [x, y] = store.front();
        store.pop();

        grid[x][y] = newColor;

        for (auto &next : options) {
            // We traverse via all the possible directions adjacent to current
            int nextX = x + next.first;
            int nextY = y + next.second;

            // And if they are not out of bounds
            if (nextX < 0 || nextX >= n) continue;
            if (nextY < 0 || nextY >= n) continue;

            // and if not visited already
            if (visited[nextX][nextY]) continue;

            // and contain the same color, then we push them into queue
            // to ber replaced during next pop iteration of queue
            if (grid[nextX][nextY] == oldCol) {
                store.push(make_pair(nextX, nextY));
                visited[nextX][nextY] = true;
            }
        }
    }
}