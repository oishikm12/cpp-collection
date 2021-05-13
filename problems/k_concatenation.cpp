#include <iostream>
#include <vector>
using namespace std;

int getMaxSubarraySum(vector<int> &, int);
int kadaneSum(vector<int> &);

int main() {
    /**
     * Instead of concatinating the subarray multiple time going exponential
     * We can instead find out the highest prefix subarray, suffix subarray
     * and add it to total sum repeated number of times in the middle
     */ 
    cout << "\nThis program finds out maximum sum subarray after repeating the given array multiple times\n" << endl;
    int n, k;
    cout << "Enter the length of the array: ";
    cin >> n;
    cout << "Enter no. of times to repeat this array: ";
    cin >> k;

    vector<int> arr(n);
    cout << "Enter space-separated elements of the array" << endl;
    for (int i = 0; i < n; i += 1) cin >> arr[i];

    int maxSum = getMaxSubarraySum(arr, k);

    cout << "\n" << maxSum << " is the maximum possible subarray sum." << endl;

    cout << endl;

    return 0;
}

int getMaxSubarraySum(vector<int> &arr, int rep) {
    // First we fetch the max possible Kadane Subarray Sum of the array
    int ksum = kadaneSum(arr);

    // If array is not repeating, kadane sum is always the max possible
    if (rep == 1) return ksum;

    // Prefix sum represents the selecting the highest sum subarray
    // such that the first element is in the subarray. Suffix sum
    // represents selecting the highest sum subarray such that the
    // last element is in the subarray
    int n = arr.size();
    int currSumPref = 0, currSumSuff = 0;
    int bestPrefix = INT_MIN, bestSuffix = INT_MIN;

    for (int i = 0; i < n; i += 1) {
        // We add each element to current position and if it is more than
        // whatever current prefix / suffix sum is, we replace it
        currSumPref += arr[i];
        bestPrefix = max(bestPrefix, currSumPref);
        currSumSuff += arr[n - i - 1];
        bestSuffix = max(bestSuffix, currSumSuff); 
    }

    int sum = currSumPref;
    int maxSum;

    // If the contigious sum is less than or equal to zero, we
    // do not need to consider total sum since it lowers the subarray sum
    // If it is greater then we add whatever total sum * n - 2 is 
    // to prefix and suffix and check if it exceeds kadane's sum
    if (sum <= 0) maxSum = max(bestPrefix + bestSuffix, ksum);
    else  maxSum = max(bestPrefix + bestSuffix + (rep - 2) * sum, ksum);

    return maxSum;
}

int kadaneSum(vector<int> &arr) {
    // Kadane Sum finds out the maximum possible sum subarray
    // by continiously adding every element to a sum variable
    // At each step we compare the sum to find the peak highest
    // sum achieved, that becomes the highest sum subarray
    int curr = 0;
    int best = INT_MIN;

    for (auto &x : arr) {
        curr += x;
        best = max(best, curr);
        // We do not consider negative values, as such we reset to 0
        // NOTE - In case of negative values, the maximum sum is
        // always the highest negative value by itself
        if (curr < 0) curr = 0;
    }

    return best;
}