#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

bool canPlace(vector<vector<int>>&, int, int, int);
bool placeNext(vector<vector<int>>&, int, int);
void prettyPrint(vector<vector<int>>&);

int main() {
    /**
     * In order to ind a solution to a sudoku board, we place a number in a
     * pos, and then check if it can be placed there, if so we recurse to place
     * a number in next position, if not, we backtrack from that position, in
     * order to change the previous element
     */ 
    cout << "\nThis program finds out a possible solution to sudoku board.\n" << endl;
    int size;
    cout << "Enter the size of board : ";
    cin >> size;

    vector<vector<int>> board(size, vector<int>(size, 0));

    cout << "Enter space delimited elements in each row of board." << endl;
    for (int i = 0; i < size; i += 1) {
        string s;
        cin >> s;
        for (int j = 0; j < size; j += 1) board[i][j] = s[j] - '0';
    }

    bool success = placeNext(board, 0, 0);

    if (!success) {
        cout << "\nThis sudoku board cannot be solved" << endl;
    } else {
        cout << "\nSolution:" << endl;
        prettyPrint(board);
    }

    cout << endl;

    return 0;
}

bool placeNext(vector<vector<int>> &board, int rowPos, int colPos) {
    int size = board.size();

    // We first check if we have reached the end of the board
    if (rowPos == size) return true;

    // We then check if we have reached the end of a column
    if (colPos == size) return placeNext(board, rowPos + 1, 0);

    // We then check if a value is already present
    if (board[rowPos][colPos] != 0) return placeNext(board, rowPos, colPos + 1);

    // We simply place the most probable value in the current position
    for (int num = 1; num <= size; num += 1) {
        if (canPlace(board, rowPos, colPos, num)) {
            board[rowPos][colPos] = num;
            // If we can also place the next element, our current selection is correct
            if (placeNext(board, rowPos, colPos + 1)) return true;
        }
    }

    // If we reach this point, then previous value is wrong, so we backtrack
    board[rowPos][colPos] = 0;
    return false;
}

bool canPlace(vector<vector<int>> &board, int rowPos, int colPos, int num) {
    int size = board.size();

    for (int i = 0; i < size; i += 1) {
        // We check entire grid for re occurence of this number
        if (board[rowPos][i] == num || board[i][colPos] == num) return false;
    }

    // We check sqrt(x) * sqrt(x) grid for recurrence of this num
    int divider = sqrt(size);
    int rowStart = (rowPos / divider) * divider;
    int colStart = (colPos / divider) * divider;

    for (int i = rowStart; i < divider + rowStart; i += 1) {
        for (int j = colStart; j < divider + colStart; j += 1) {
            // This would mean that this number is already presnt 
            if (board[i][j] == num) return false;
        }
    }

    return true;
}

void prettyPrint(vector<vector<int>>& grid) {
    int size = grid.size();
    int divider = sqrt(size);

    for (int i = 0; i < size; i += 1) {
        if (i % divider == 0) cout << endl;
        for (int j = 0; j < size; j += 1) {
            if (j != 0 && j % divider == 0) cout << " ";
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}