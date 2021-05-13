#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int merge(vector<int>&, int, int, int);
int getInversions(vector<int>&, int, int);

int main() {
    /**
     * In order to find out all possible inversions such that the
     * array itself becomes sorted we will use merge sort, as during 
     * merging of two sorted arrays we know exactly how many are
     * greater than current
     */ 
    cout << "\nThis problem finds out number of inversions in unsorted array\n" << endl;
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "\nEnter space seperated elements of array." << endl;
    for (int i = 0; i < n; i += 1) cin >> arr[i];

    int inversions = getInversions(arr, 0, arr.size() - 1);

    cout << "There are " << inversions << " possible inversions." << endl;

    cout << endl;

    return 0;
}

int merge(vector<int> &arr, int low, int mid, int high) {
    int i = low;
    int j = mid + 1;
    int k = 0;
    int cnt = 0;
    vector<int> sorted(high - low + 1);

    while (i <= mid && j <= high) {
        if (arr[i] <= arr[j]) {
            sorted[k++] = arr[i++];
        } else {
            // When an element of right subarry is smaller
            // we will have to invert all elements still in
            // left subarray to make it reach the desired pos
            sorted[k++] = arr[j++];
            cnt += (mid - i + 1);
        }
    }

    while (i <= mid) sorted[k++] = arr[i++];
    while (j <= high) sorted[k++] = arr[j++];

    k = 0;
    for (int t = low; t <= high; t += 1) arr[t] = sorted[k++];

    return cnt;
}

int getInversions(vector<int> &arr, int low, int high) {
    // We have sorted the entire array, all inversions found
    if (low >= high) return 0;

    // By basis of binary search w find all inversions to left & right
    int mid = low + (high - low) / 2;
    int leftCount = getInversions(arr, low, mid);
    int rightCount = getInversions(arr, mid + 1, high);
    int mergeCount = merge(arr, low, mid, high);

    return leftCount + rightCount + mergeCount;
}