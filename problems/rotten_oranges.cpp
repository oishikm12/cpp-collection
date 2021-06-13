#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    /**
     * In order to find the total time required to rot all oranges, we use
     * a queue to store all rotting coordinates in the current time frame 
     * and add all sections rotting in this time frame inside queue for next 
     * iteration. The number of iteration gives us the time frame
     */
    cout << "\nThis program finds out the total time required before all oranges rot in a mixture of fresh & rotting oranges.\n" << endl;
    int row, col;
    cout << "Enter vertical length of the grid: ";
    cin >> row;
    cout << "Enter horizontal length of the grid: ";
    cin >> col;
    
    vector<vector<int>> grid(row, vector<int>(col));
    cout << "Enter space seperated, line delimited elements of the grid, where 0 represents empty, 1 for fresh & 2 for rot," << endl;
    for (int i = 0; i < row; i += 1) for (int j = 0; j < col; j += 1) cin >> grid[i][j];

    int timeElapse = orangesRotting(grid);

    if (timeElapse == -1) cout << "\nAll oranges will never rot, they are too far away." << endl;
    else cout << "\nIt will take " << timeElapse << " units of time for all oranges to rot." << endl;

    cout << endl;

    return 0;
}

int orangesRotting(vector<vector<int>>& grid) {
    queue<pair<int, int>> q;
    int time = 0;
    
    int n = grid.size();
    int m = grid[0].size();
    
    // Store all the cells having rotten orange in first time frame
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            if (grid[i][j] == 2) q.push(make_pair(i, j));
        }
    }

    // All possible 4 directions that can be traversed from a section
    vector<pair<int, int>> next = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    
    while (!q.empty()) {
        // We only want to traverse oranges already rotting when
        // current loop started, so we store size
        int lim = q.size();
        
        for (int i = 0; i < lim; i += 1) {
            auto [x, y] = q.front();
            q.pop();

            for (int i = 0; i < 4; i += 1) {
                // We traverse all adjacent sections to a grid to check
                // if we can rot the oranges there
                int newX = x + next[i].first;
                int newY = y + next[i].second;

                // We need to check if the adjacent section is inside grid
                // and if an orange exists and it is fresh
                if (newX > -1 && newX < n && newY > -1 && newY < m && grid[newX][newY] == 1) {
                    // Turn this orange bad, and reinsert for next round
                    grid[newX][newY] = 2;
                    q.push(make_pair(newX, newY));
                }
            }
        }

        // This size of queue determines whether even a single fresh
        // orange gets rotten due to rotten oranges in current time
        // frame so we can increase the count of the required time.
        if (!q.empty()) time += 1;
    }
    
    // Return -1 if all oranges did not rot, otherwise return time
    for (auto &x : grid) {
        for (auto &y : x) if (y == 1) return -1;
    }

    return time;
}