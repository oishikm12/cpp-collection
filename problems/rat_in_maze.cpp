#include <iostream>
#include <vector>
using namespace std;

bool findNextPath(vector<string>&, int, int);
void printPath(vector<string>&);

int main() {
    /**
     * In order to find multiple possible paths starting point, we recurse
     * such that for each poistion, next position could either be bottom
     * or right. If we reach destinition we recurse, or if the next pos
     * is invalid we recurse
     */ 
    cout << "\nThis program finds out a path in a maze.\n" << endl;
    int size;
    cout << "Enter the size of grid : ";
    cin >> size;

    vector<string> board(size);

    cout << "Enter the positions of obstacles in the grid." << endl;
    for (int i = 0; i < size; i += 1) cin >> board[i];

    cout << "\nSeacrching for possible paths" << endl;

    bool success = findNextPath(board, 0, 0);

    if (!success) {
        cout << "\nThere were no possible solutions to destination" << endl;
    }

    cout << endl;

    return 0;
}

bool findNextPath(vector<string> &grid, int rowPos, int colPos) {
    int size = grid.size() - 1;

    // We have to check if we have rechead destinition
    if (rowPos == size && colPos == size) {
        printPath(grid);
        return true;
    }

    // We need to check if we have exited the grid
    if (rowPos > size || colPos > size) return false;

    // We need to check if the current pos is prohibited
    if (grid[rowPos][colPos] == 'X' || grid[rowPos][colPos] == 'x') return false;

    // We set the current pos as visited
    grid[rowPos][colPos] = '1';

    bool rightSuccess = findNextPath(grid, rowPos, colPos + 1);
    bool downSuccess = findNextPath(grid, rowPos + 1, colPos);

    // Backtrack from this position
    grid[rowPos][colPos] = '0';

    if (rightSuccess || downSuccess) return true;

    return false;
}

void printPath(vector<string>& grid) {
    for (int i = 0; i < grid.size(); i += 1) {
        for (int j = 0; j < grid.size(); j += 1) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}