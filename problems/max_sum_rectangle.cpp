#include <iostream>
#include <vector>
using namespace std;

int getKadaneSum(vector<int> &);
int getMaxSumRect(vector<vector<int>> &);

int main() {
    /**
     * In order to find out the maximal sum of rectangle possible
     * in a given grid, we simply set 2 pointers across columns,
     * both starting at the same, however the 2nd pointer, traversing
     * till end for each increment of the 1st. During this traversal
     * we maintain cumulative sum row wise of each row in an array.
     * Kadane Sum of this array at each step, gives us the max possible
     * value of rectangle at that point
     */ 
    cout << "\nThis program finds out the maximal sum rectangle in a given grid.\n" << endl;
    int n, m;
    cout << "Enter length of the grid: ";
    cin >> n;
    cout << "Enter breadth of the grid: ";
    cin >> m;

    vector<vector<int>> grid(n, vector<int>(m));
    cout << "Enter space seperated, line delimited elements of the grid," << endl;
    for (int i = 0; i < n; i += 1) for (int j = 0; j < m; j += 1) cin >> grid[i][j];

    int maxVal = getMaxSumRect(grid);

    cout << "\nThe maximal sum rectangle possible in this grid is: " << maxVal << "." << endl;

    cout << endl;

    return 0;
}

int getKadaneSum(vector<int> &sum) {
    int maxSum = INT_MIN;
    int curr = 0;
    
    for (auto &x : sum) {
        // Kadane's Sum works on the simple logic
        // of adding each element to an accumalator,
        // wherein while the accumulator is positive,
        // we store / compare it for max value. When
        // it reaches negative, we reset sum to 0
        curr += x;
        maxSum = max(maxSum, curr);
        if (curr < 0) curr = 0;
    }
    
    // This represents the maximum subarray sum, in our
    // case it represents maximum rectangular sum since
    // sum of rows are stored in each index
    return maxSum;
}

int getMaxSumRect(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();
    
    // We keep a variable of maxSum to compare and
    // store the largest rectangle sum. The sum array
    // simply keeps cumulative sum of rows in each index
    vector<int> sum(n);
    int maxSum = INT_MIN;
    
    for (int left = 0; left < m; left += 1) {
        // Reseting all values of sum to 0, when changing left pointer
        for (auto &x : sum) x = 0;
        
        for (int right = left; right < m; right += 1) {
            // The sum array simply stores the cumulative sum of 
            // rows, when the right pointer of column increases
            for (int i = 0; i < n; i += 1) sum[i] += grid[i][right];
            // At each step after increment, we find out the kadane
            // sum, this gives us the maximal possible rectangle sum,
            // since each element of the sum array is sum of all 
            // elements from left to right in that row
            maxSum = max(maxSum, getKadaneSum(sum));
        }
    }
    
    return maxSum;
}