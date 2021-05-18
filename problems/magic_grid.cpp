#include <iostream>
#include <vector>
using namespace std;

int main() {
    /**
     * In order to find the minimal needed starting cost, we
     * will start from the ending point assuming we reached
     * that position with 1 energy remaining, thereupon, we will
     * backtrack to the path with minimal energy required
     */ 
    cout << "\nThis program determines the minimum starting cost needed to traverse a path of negatives & positives and reach the end with positive value.\n" << endl;
    int rows, cols;
    cout << "Enter the rows in the path grid: ";
    cin >> rows;
    cout << "Enter the columns in the path grid: ";
    cin >> cols;

    vector<vector<int>> grid(rows, vector<int>(cols));
    cout << "Enter space seperated columns & line delimted rows of the grid," << endl;
    for (int i = 0; i < rows; i += 1) for (int j = 0; j < cols; j += 1) cin >> grid[i][j];

    int minCost = getMagicGrid(grid);

    cout << "\nThe minimal starting cost needed to reach the ending alive is " << minCost << "." << endl;

    cout << endl;

    return 0;
}

int getMagicGrid(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> dp(n, vector<int>(m));
    // Assuming we end with 1 energy point left
    // i.e to reach this point we needed 1 energy
    dp[n - 1][m - 1] = 1;

    // The reason we subtract each value from the
    // dp array, is because positive energies add to
    // our present collection, as such we need that much
    // less energy to reach that grid. Negative values 
    // means that we needed that much energy so our 
    // total reserve remains positive

    // First we precompute along the rows
    // The reason being there is no right in last col
    for (int i = n - 2; i >= 0; i -= 1) {
        // The only time it goes to negative, is if the
        // grid gives us lots of energy, however minimum 1
        // energy must be maintained throughout the journey
        dp[i][m - 1] = max(dp[i + 1][m - 1] - grid[i][m - 1], 1);
    }
    
    // Then we precompute the columns
    // The reason being there is no bottom in last row
    for (int i = m - 2; i >= 0; i -= 1) {
        dp[n - 1][i] = max(dp[n - 1][i + 1] - grid[n - 1][i], 1);
    }
    
    for (int i = n - 2; i >= 0; i -= 1) {
        for (int j = m - 2; j >= 0; j -= 1) {
            // At each step we have to check wether
            // travelling from left or from top costs us less
            int curr = min(dp[i][j + 1], dp[i + 1][j]);
            dp[i][j] = max(curr - grid[i][j], 1);
        }
    }
    
    return dp[0][0];
}