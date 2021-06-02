#include <iostream>
#include <vector>
using namespace std;

bool getSubsetSum(vector<int> &, int);

int main() {
    /**
     * In order to find the sum of elements that equal a certain
     * value, we will maintain a 2D matrix, where each row represents
     * addition of a certain element, and each column represents 
     * the sum attained
     */ 
    cout << "\nThis program finds if the sum of subsets of an array, equals a certain sum.\n" << endl;
    int n, sum;
    cout << "Enter number of items to consider: ";
    cin >> n;
    cout << "Enter desired sum to attain: ";
    cin >> sum;

    vector<int> arr(n);

    cout << "Enter space elements of the array," << endl;
    for (int i = 0; i < n; i += 1) cin >> arr[i];

    bool isPossible = getSubsetSum(arr, sum);

    if (isPossible) cout << "\nIt is possible to attain " << sum << "." << endl;
    else cout << "\nNo sum of subsets gives us " << sum << "." << endl;

    cout << endl;

    return 0;
}

bool getSubsetSum(vector<int> &arr, int sum) {
    int n = arr.size();
    // The rows represent element selected, columns, the sum to attain
    vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));

    // A sum of 0 is possible with every element
    for (int i = 0; i <= n; i += 1) dp[i][0] = true; 
    
    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= sum; j += 1) {
            if (j < arr[i - 1]) {
                // If the current element is less than the total
                // sum, then we simply check if the current sum
                // was reachable via any combination of previous elements
                dp[i][j] = dp[i - 1][j];
            } else {
                // Otherwise we check if it is reachable via adding
                // the current element, or if it was already reachable
                // NOTE: We simply subtract the current value from
                //      sum, cause if it was possible to reach that
                //       point, current sum can be reached, by adding this element
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - arr[i - 1]];
            }
        }
    }
    
    return dp[n][sum];
}