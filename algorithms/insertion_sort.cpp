#include <iostream>
#include <vector>
using namespace std;

void insertion(vector<int>&, int);

int main() {
    /**
     * Insertion Sort works in n^2 time, by swapping adjacent elements
     * till the current element is in its desired pos
     */ 
    cout << "\nThis program sorts a given array via selection sort.\n" << endl;
    int len;
    cout << "Enter length of array : ";
    cin >> len;
    
    vector<int> arr(len);

    cout << "Enter space seperated elements of array," << endl;
    for (int i = 0; i < len; i += 1) cin >> arr[i];

    insertion(arr, len);

    cout << "\nThe sorted array is," << endl;
    for (int i = 0; i < len; i += 1) {
        cout << arr[i];
        if (i == len - 1) cout << endl;
        else cout << ", ";
    }

    cout << endl;

    return 0;
}

void insertion(vector<int> &arr, int len) {
    // We simply shift each element relative to selected element
    for (int i = 1; i < len; i += 1) {
        int curr = arr[i];
        int j = i - 1;
        // Placing each element of j at j + 1 shifts them to the right
        // provided they are greater than the current element
        while (arr[j] > curr && j >= 0) {
            arr[j + 1] = arr[j];
            j -= 1;
        }
        // We want to place the current at its desired pos
        arr[j + 1] = curr;
    }
}