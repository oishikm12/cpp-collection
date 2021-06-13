#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int maxRectangularArea(vector<vector<int>> &); 
int maxAreaTillHere(vector<int> &, int);

int main() {
    /**
     * In order for us to find out the largest area covered by a binary rectangle 
     * of a matrix we will add the value of each column to the columns in next row,
     * treating each grid as a bar, this in turn will allow us to determine highest
     * horizontal length & vertical height of each row giving us area of rectangle
     */ 
    cout << "\nThis program finds out the maximum size of a rectangle in a binary matrix.\n" << endl;
    int row, col;
    cout << "Enter the height of this grid: ";
    cin >> row;
    cout << "Enter the width of this grid: ";
    cin >> col;

    vector<vector<int>> grid(row, vector<int>(col));
    cout << "Enter space seperated, line delimited elements of the grid," << endl;
    for (int i = 0; i < row; i += 1) for (int j = 0; j < col; j += 1) cin >> grid[i][j];

    int area = maxRectangularArea(grid);

    cout << "\nThe maximum area of rectangle consisting of only 1s in this grid is " << area << "." << endl;

    cout << endl;

    return 0;
}

int maxRectangularArea(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    // Calculate area for first row and initialize it as result
    int result = maxAreaTillHere(grid[0], m);

    // Iterate over every rows and add value of previous rows to same column
    for (int i = 1; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            // We only add the value of previous row to current row, same column
            // only if the value there was 1, since it ensures rectangle is continued
            if (grid[i][j] == 1) grid[i][j] += grid[i - 1][j];
        }

        result = max(result, maxAreaTillHere(grid[i], m));
    }

    return result;
}

int maxAreaTillHere(vector<int> &row, int m) {
    // We only consider non zero elements, as such
    // we sort the elements in increaing order via stack
    stack<int> result;
 
    // Maximum area & current area with top
    int maxArea = 0;
    int area = 0;
 
    // Run through all cumulative values of heights of rows
    int i = 0;
    while (i < m) {
        // If this bar is higher than the bar on top stack, push it to stack
        if (result.empty() || row[result.top()] <= row[i]) result.push(i++);
        else {
            // If this bar is lower than top of stack, then
            // calculate area of rectangle with stack top as
            // the smallest (or minimum height) bar. 'i' is
            // 'right index' for the top and element before
            // top in stack is 'left index'
            int topVal = row[result.top()];
            result.pop();
            area = topVal * i;
 
            if (!result.empty()) area = topVal * (i - result.top() - 1);

            maxArea = max(area, maxArea);
        }
    }
 
    // Now pop the remaining bars from stack and calculate
    // area with every popped bar as the smallest bar
    while (!result.empty()) {
        int topVal = row[result.top()];
        result.pop();
        area = topVal * i;

        if (!result.empty()) area = topVal * (i - result.top() - 1);

        maxArea = max(area, maxArea);
    }

    return maxArea;
}