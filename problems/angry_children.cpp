#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int getUnfairness(vector<int> &, int);

int main() {
    /**
     * In order to select k adjacent elements amidst sorted
     * sequence such that the absolute difference remains minimal
     * we can use dynamic programming to keep track of deletions
     * and inclusions based on cumulative Sum of elements
     */ 
    cout << "\nThis program selects an arbitary number of elements from a sequence such that absolute distance between them is minimal.\n" << endl;
    int n, k;
    cout << "Enter the length of sequence to consider: ";
    cin >> n;
    cout << "Enter the number of elements to select: ";
    cin >> k;

    vector<int> elems(n);
    cout << "Enter space seperated elements of the sequence," << endl;
    for (int i = 0; i < n; i += 1) cin >> elems[i];

    int unfairness = getUnfairness(elems, k);

    cout << "\nAfter selecting " << k << " elements the minimal absolute distance is " << unfairness << "." << endl;

    cout << endl;

    return 0;
}

int getUnfairness(vector<int> &elems, int k) {
    int n = elems.size();
    vector<int> dp(n), cumSum(n);
    
    // First we sort the elements in ascending order
    // This way we have to select consequitive k elements
    sort(elems.begin(), elems.end());
    
    // We calculate the cumulative sum of elements next
    cumSum[0] = elems[0];
    for (int i = 1; i < n; i += 1) cumSum[i] = cumSum[i - 1] + elems[i];
    
    // Next we calculate the unfairness cost of first k elems:
    // x2 - x1 + x3 - x1 ... xk - xk-1 => This can be shortened
    // unfairness at k = (val at k) * (k - 1) - sum uptil k
    for (int i = 1; i < k; i += 1) dp[k - 1] += i * elems[i] - cumSum[i - 1];

    for (int i = k; i < n; i += 1) {
        // Whenever we need to a add a new element we remove the old
        // x2 - x1, x3 - x1 ... all need to be removed, this can be
        // shortened to cumSum(elem after del -> elem before curr)
        // Similarly for adding a new one cumSum(...), thus the formulae
        // oldSum - 2 * cumSum(...) + k-1 * elem to del + k-1 * elem to add
        dp[i] = dp[i - 1] - 2 * (cumSum[i - 1] - cumSum[i - k]) + (k - 1) * elems[i - k] + (k - 1) * elems[i];
    }

    // We need the minimal costing one from here
    int ans = *min_element(dp.begin() + k - 1, dp.end());
    
    return ans;
}