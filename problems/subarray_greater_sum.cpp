#include <iostream>
#include <vector>
using namespace std;

int smallestSubArr(vector<int> &, int, int);

int main() {
    /**
     * In order to find out the minimal subarray size whose sum is just
     * greater than the given sum, we will maintain two running pointers
     * incrementing the lagging pointer when sum exceeds given number,
     * and incrementing fast pointer when sum has not reached the given
     * number, at every stage, the difference between them will give us size
     */ 
    cout << "\nThis program finds out minimal subarray size such that the sum exceeds a given number.\n" << endl;
    int n, sum;
    cout << "Enter the size of the array to consider: ";
    cin >> n;
    cout << "Enter the sum to exceed: ";
    cin >> sum;

    vector<int> arr(n);
    cout << "Enter space seperated elements of the list to consider," << endl;
    for (int i = 0; i < n; i += 1) cin >> arr[i];

    int length = smallestSubArr(arr, n, sum);

    if (length == n + 1) cout << "There is no subarray whose sum exceeds " << sum << "." << endl;
    cout << "\nWe will need a subarray of size " << length << " to get a sum which exceeds " << sum << "." << endl;

    cout << endl;

    return 0;
}

int smallestSubArr(vector<int> &arr, int n, int sum) {
    // Initialize current sum and minimum length
    int currSum = 0;
    int minLen = n + 1;

    // Initialize starting and ending indexes
    int start = 0;
    int end = 0;

    while (end < n) {
        // Keep adding array elements while current sum
        // is smaller than or equal to x
        while (currSum <= sum && end < n) {
            currSum += arr[end];
            end += 1;
        }

        // If current sum becomes greater than x.
        while (currSum > sum && start < n) {
            // Update minimum length if needed
            minLen = min(minLen, end - start);
            // Remove starting elements
            currSum -= arr[start++];
        }
    }

    return minLen;
}
