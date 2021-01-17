#include <iostream>
#include <vector>
using namespace std;

void selection(vector<int>&, int);

int main() {
    /**
     * Selection Sort works in n^2 time, by swapping elements with desired position
     */ 
    cout << "\nThis program sorts a given array via selection sort.\n" << endl;
    int len;
    cout << "Enter length of array : ";
    cin >> len;

    vector<int> arr(len);

    cout << "Enter space seperated elements of array," << endl;
    for (int i = 0; i < len; i += 1) cin >> arr[i];

    selection(arr, len);

    cout << "\nThe sorted array is," << endl;
    for (int i = 0; i < len; i += 1) {
        cout << arr[i];
        if (i == len - 1) cout << endl;
        else cout << ", ";
    }

    cout << endl;

    return 0;
}

void selection(vector<int> &arr, int len) {
    for (int i = 0; i < len - 1; i += 1) {
        // We need to swap min index with actual min
        int minIndex = i;

        for (int j = i + 1; j < len ; j += 1) {
            if (arr[minIndex] > arr[j]) {
                // This way our index will always be min
                minIndex = j;
            }
        }
        // Simply swap them

        swap(arr[i], arr[minIndex]);
    }
}