#include <iostream>
#include <vector>
using namespace std;

vector<int> zigZagTrav(vector<vector<int>> &);

int main() {
    /**
     * In order to store elements in a zig zag fashion,
     * we will be maintaing two flags, one to denote which
     * direction to travel to, and another to check if it
     * is even turn (top to down) or odd (down to top)
     */ 
    cout << "\nThis program prints a matrix in a zig-zag fashion\n" << endl;
    int row, col;
    cout << "Enter no. of rows in the matrix: ";
    cin >> row;
    cout << "Enter no. of columns in the matrix: ";
    cin >> col;

    vector<vector<int>> matrix(row, vector<int>(col));
    cout << "Enter space seperated colums, line delimited rows of the matrix,";
    for (int i = 0; i < row; i += 1) for (int j = 0; j < col; j += 1) cin >> matrix[i][j];

    vector<int> result = zigZagTrav(matrix);

    cout << "\nZig-Zag traversal of the matrix is," << endl;
    for (auto &x : result) cout << x << " ";

    cout << endl << endl;

    return 0;
}

vector<int> zigZagTrav(vector<vector<int>> &matrix) {
    int height = matrix.size() - 1;
    int width = matrix[0].size() - 1;
    vector<int> result;

    int row = 0, col = 0;
    bool goingDown = true;
    
    // We will continue till we reach the end of matrix
    while (row >= 0 && row <= height && col >= 0 && col <= width) {
        // We enter the current element into the list
        result.push_back(matrix[row][col]);
    
        if (goingDown) {
            // We are at odd bunch so we are traversing down (bottom-left)
            if (col == 0 || row == height) {
                // We have reached a border
                goingDown = false;

                // If there is no bottom row left we move right
                // else we move down & then up next turn
                if (row == height) col += 1;
                else row += 1;

                continue;
            }
            row += 1;
            col -= 1;
        } else {
            // We are at even bunch so we are traversing up (top-right)
            if (row == 0 || col == width) {
                // We have reached a border
                goingDown = true;
                
                // If there is no right column, we move down
                // else we move right & then down next turn
                if (col == width) row += 1;
                else col += 1;

                continue;
            }
            row -= 1;
            col += 1;
        }
    }

    return result;
}