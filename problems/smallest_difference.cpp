#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    /**
     * In order to find the smallest difference between elements
     * of tewo arrays, we will first sort them, after that we will
     * use two seperate iterators increasing one when distance is
     * less and incrementing other when distance is less
     */ 
    cout << "\nThis program finds the difference of two numbers having minimal distance between two arrays.\n" << endl;
    int n, m;
    cout << "Enter the size of the first array: ";
    cin >> n;
    cout << "Enter the size of the second array: ";
    cin >> m;

    vector<int> arr1(n), arr2(m);
    cout << "Enter space seperated elements of the first array," << endl;
    for (int i = 0; i < n; i += 1) cin >> arr1[i];
    cout << "Enter space seperated elements of the second array," << endl;
    for (int i = 0; i < m; i += 1) cin >> arr2[i];

    // We first sort these arrays so we know that
    // L to R is always increasing in value
    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());

    // We use these to iterate over the arrays
    int i = 0, j = 0;
    int leastDiff = INT_MAX;

    while (i < n && j < n) {
        int diff = abs(arr1[i] - arr2[j]);
        leastDiff = min(leastDiff, diff);

        // If the element in the first array is smaller
        // we increament its iterator otherwise the iterator
        // of the second array is incremented
        if (arr1[i] < arr2[j]) i += 1;
        else j += 1;
    }

    cout << "\nThe smalles possible difference between these arrays is: " << leastDiff << "." << endl;

    cout << endl;

    return 0;
}