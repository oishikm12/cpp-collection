#include <iostream>
#include <vector>
using namespace std;

int getMedian(vector<int> &, vector<int> &, int);
int median(vector<int> &, int);

int main() {
    /**
     * In order to find the median of two sorted arrays, when they are
     * combined, we simply find out the most suitable position for such
     * a median to exist, by comparing the individual medians of the two
     * arrays, the one which is lower moves up, while the higher moves
     * down, till the size of vectors reduces to 2 or less
     */ 
    cout << "\nThis program finds out the median of two sorted arrays of same size when combined.\n" << endl;
    int n;
    cout << "Enter the number of elements to consider: ";
    cin >> n;

    vector<int> arr1(n), arr2(n);
    cout << "Enter space seperated sorted elements of the first array," << endl;
    for (int i = 0; i < n; i += 1) cin >> arr1[i];
    cout << "Enter space seperated sorted elements of the second array," << endl;
    for (int i = 0; i < n; i += 1) cin >> arr2[i];

    int mdn = getMedian(arr1, arr2, n);

    cout << "\nThe median of the arrays when combined, turns out to be " << mdn << "." << endl;

    cout << endl;

    return 0;
}

int median(vector<int> &arr, int n) {
    // Median lies in middle for odd number of elements, and
    // average of two middle numbers for even number of elements
    if (n % 2 == 0) return (arr[n / 2] + arr[n / 2 - 1]) / 2;
    else return arr[n / 2];
}

int getMedian(vector<int> &arr1, vector<int> &arr2, int n) {
    // Base Case for invalid input
    if (n <= 0) return 0;
    // When there is 1 element remaining in both, we simply return their average
    if (n == 1) return (arr1[0] + arr2[0]) / 2;
    // When there are 2 elements in both, we find average of max of 1st & min of 2nd indices
    if (n == 2) return (max(arr1[0], arr2[0]) + min(arr1[1], arr2[1])) / 2;

    int m1 = median(arr1, n);
    int m2 = median(arr2, n);

    // If the medians are equal, we return either
    if (m1 == m2) return m1;

    // Next size after determining median position
    int sz = n & 1 ? n / 2 : n / 2 - 1;

    if (m1 < m2) {
        // If m1 < m2 then median must exist in arr1[m1....] and arr2[....m2]
        arr1.erase(arr1.begin(), arr1.begin() + sz);
        return getMedian(arr1, arr2, n - sz);
    } else {
        // If m1 > m2 then median must exist in arr1[....m1] and arr2[m2...]
        arr2.erase(arr2.begin(), arr2.begin() + sz);
        return getMedian(arr2, arr1, n - sz);
    }
}