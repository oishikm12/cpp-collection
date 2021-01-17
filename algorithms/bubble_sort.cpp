#include <iostream>
#include <vector>
using namespace std;

void bubble(vector<int>&, int);

int main() {
    /**
     * Bubble Sort works in n^2 time, by iterating over array elements twice
     */ 
    cout << "\nThis program sorts a given array via bubble sort.\n" << endl;
    int len;
    cout << "Enter length of array : ";
    cin >> len;

    vector<int> arr(len);

    cout << "Enter space seperated elements of array," << endl;
    for (int i = 0; i < len; i += 1) cin >> arr[i];

    bubble(arr, len);

    cout << "\nThe sorted array is," << endl;
    for (int i = 0; i < len; i += 1) {
        cout << arr[i];
        if (i == len - 1) cout << endl;
        else cout << ", ";
    }

    cout << endl;

    return 0;
}

void bubble(vector<int> &arr, int len) {
    // We do not need to run for last iteration
    for (int i = 0; i < len - 1; i += 1) {
        for (int j = 0; j < len - i - 1; j += 1) {
            if (arr[j] > arr[j + 1]) {
                // This way the element at the end will always be the greatest
                // Hence we ignore the last one (j - i) in each iteration
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}