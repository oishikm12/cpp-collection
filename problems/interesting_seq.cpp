#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    /**
     * In order to convert the sequence to interesting we will
     * simply compare the cost to convert them into all possible
     * values between 1 & n and select the minimal costing one
     */ 
    cout << "\nThis program finds out the minimum cost to convert a sequence to interesting.\n" << endl;
    int n, cost_incDec, cost_inc;
    cout << "Enter the number of elements in this sequence: ";
    cin >> n;
    cout << "Enter the cost to increment one & decrement another: ";
    cin >> cost_incDec;
    cout << "Enter the cost to just increment an element: ";
    cin >> cost_inc;

    vector<int> arr(n);
    cout << "Enter space seperated current elements of the array," << endl;
    for (int i = 0; i < n; i += 1) cin >> arr[i];

    // In order to see the possible conversions, we need to sort
    sort(arr.begin(), arr.end());

    // We consider the minimum cost to be the max first
    int ans = INFINITY;

    // We traverse over all possible value of elements in
    // the array, the max value is always the greatest in arr
    for (int i = arr[0]; i <= arr[n - 1]; i += 1) {
        int inc = 0, dec = 0;
        
        // In order to find out what is the minimum possible
        // cost we consider all values to be the final, and
        // check associated conversions to convert them into that
        for (auto &a : arr) {
            if (a < i) inc += (i - a);
            else dec += (a - i);
        }
        
        // The number of values to decrement must always be
        // equal or less than increment as per requirement
        if (dec > inc) continue;
        
        ans = min(ans, dec * cost_incDec + (inc - dec) * cost_inc);
    }

    cout << "\nThe cost to convert them all to the same is : " << ans << "." << endl;

    cout << endl;

    return 0;
}