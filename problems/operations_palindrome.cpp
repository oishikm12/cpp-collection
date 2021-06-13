#include <iostream>
#include <vector>
using namespace std;

int findMinOps(vector<int> &, int, int);

int main() {
    /**
     * 
     */
    cout << "\nThis program finds out the minimal number of combining operations needed to make an array palindromic.\n" << endl; 
    int n;
    cout << "Enter the number of elements to consider: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter space seperated elements of the array," << endl;
    for (int i = 0; i < n; i += 1) cin >> arr[i];

    // We start from two corners
    int operations = findMinOps(arr, 0, n - 1);

    cout << "\nIt will take us " << operations << " combining operations to make the array palindromic." << endl;

    cout << endl;

    return 0;
}

int findMinOps(vector<int> &arr, int iPos, int jPos) {
    // Base condition when we reach the center of the array itself
    if (iPos > jPos) return 0;

    // If corner elements are same, problem reduces arr[i+1..j-1]
    if (arr[iPos] == arr[jPos]) return findMinOps(arr, iPos + 1, jPos - 1);

    if (arr[iPos] > arr[jPos]) {
        // If left element is greater, then we merge right two elements
        arr[jPos - 1] += arr[jPos];
        return 1 + findMinOps(arr, iPos, jPos - 1);
    } else {
        // Else we merge left two elements, either costs us 1 operation
        arr[iPos + 1] += arr[iPos];
        return 1 + findMinOps(arr, iPos + 1, jPos);
    }
}