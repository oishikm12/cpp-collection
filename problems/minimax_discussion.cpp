#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    /**
     * In order to find the minimal difference after substraction
     * or addition of k, we will first sort the elements and then 
     * simply iterate to find out the best suitable smaller or 
     * greater element for minimal difference
     */ 
    cout << "\nThis program finds out the minimal difference after adding / subtracting a certain number to all elements.\n" << endl;
    int n, k;
    cout << "Enter the number of elements to consider: ";
    cin >> n;
    cout << "Enter the modifier to add or subtract: ";
    cin >> k;

    vector<int> arr(n);
    cout << "Enter space seperated elements of the array," << endl;
    for (int i = 0; i < n; i += 1) cin >> arr[i];

    int minDiff = getMinDifference(arr, n, k);

    cout << "\nThe minimal difference after modification is " << minDiff << "." << endl;

    cout << endl;

    return 0;
}

int getMinDifference(vector<int> &arr, int n, int k) {
    // First we sort the elements to ensure the greatest element
    // is the last, and the smallest is the first one
    sort(arr.begin(), arr.end());

    // This represents the initial difference, without any
    // modification, or if the same modification is applied to both
    // the first and the last element
    int diff = arr[n - 1] - arr[0];

    // At every step, we will maintain the biggest and the smallest
    // after each operation, so that we can find the minimal difference
    int big = max(arr[n - 1] - k, arr[0] + k);
    int small = min(arr[n - 1] - k, arr[0] + k);

    for (int i = 1; i < n - 1; i += 1) {
        int add = arr[i] + k;
        int sub = arr[i] - k;

        // Since these are inside current limits, the addition or
        // subtraction of k would not make them biggest or smallest
        if (sub >= small || add <= big) continue;

        // Otherwise we check if the difference is smaller with new values
        if (big - sub <= add - small) small = sub;
        else big = add;
    }

    return min(diff, big - small);
}