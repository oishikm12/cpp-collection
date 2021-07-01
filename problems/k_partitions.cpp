#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

bool isPartitionPossible(vector<int> &, int, int);
bool isKPartition(vector<int> &, vector<int> &, vector<bool> &, int, int, int, int, int);

int main() {
    /**
     * In order to find out if k subsets are possible, we simply
     * find out the cumulative sum of all elements and divide it k
     * times. Thereby, each subset selects elements to reach that
     * cumulative sum divided by k
     */ 
    cout << "\nThis program partitions a given array into k equal sum subsets.\n" << endl;
    int n, k;
    cout << "Enter the number of elements to consider: ";
    cin >> n;
    cout << "Enter the number of subsets to find: ";
    cin >> k;

    vector<int> arr(n);
    cout << "Enter space seperated elements of the array," << endl;
    for (int i = 0; i < n; i += 1) cin >> arr[i];

    bool canBeDivided = isPartitionPossible(arr, n, k);

    if (canBeDivided) cout << "\nThe array can be divided into " << k << " equal sum subsets." << endl;
    else cout << "\nThis array cannot be divided into " << k << " equal sum subsets." << endl;

    cout << endl;

    return 0;
}

bool isPartitionPossible(vector<int> &arr, int n, int k) {
    // If we need a single subset, the array is the result
    if (k == 1) return true;

    // If we need more partitions, than elements, then its impossible
    if (n < k) return false;

    // If the cumulative sum of all elements cannot be divided
    // into k parts, then we will not get k equal sum subsets
    int sum = accumulate(arr.begin(), arr.end(), 0);
    if (sum % k != 0) return false;

    int desiredSum = sum / k;

    vector<int> subsetSum(k, 0);
    vector<bool> selected(n, false);

    // We start by including the first element
    subsetSum[0] = arr[n - 1];
    selected[n - 1] = true;

    return isKPartition(arr, subsetSum, selected, desiredSum, k, n, 0, n - 1);
}

bool isKPartition(vector<int> &arr, vector<int> &subsetSum, vector<bool> &selected, int desiredSum, int k, int n, int currIdx, int limIdx) {
    if (subsetSum[currIdx] == desiredSum) {
        // Current index (K - 2) represents (K - 1) subsets of equal
        // sum last partition will already remain with sum 'subset
        if (currIdx == k - 2) return true;
  
        //  Recursive call for next Subset
        return isKPartition(arr, subsetSum, selected, desiredSum, k, n, currIdx + 1, n - 1);
    }
  
    // Start from limIdx and include elements into current partition
    for (int i = limIdx; i >= 0; i -= 1) {
        //  We ignore if the item is already taken
        if (selected[i]) continue;

        int currSum = subsetSum[currIdx] + arr[i];
        // We only select this item, if it the sum is less or equal to desired
        if (currSum > desiredSum) continue;

        selected[i] = true;
        subsetSum[currIdx] += arr[i];

        // After selecting the current element we recurse to select the next
        // item to be included in this subset
        bool next = isKPartition(arr, subsetSum, selected, desiredSum, k, n, currIdx, i - 1);

        // Backtracking after return, we unselect the item
        selected[i] = false;
        subsetSum[currIdx] -= arr[i];

        if (next) return true;
    }

    return false;
}