#include <iostream>
#include <vector>
using namespace std;

void recombine(vector<int>&, int, int, int);
void merge(vector<int>&, int, int);

int main() {
    /**
     * Merge Sort divides a list into two halves, till each half consists of
     * only 1 element, it then reconstructs the array combining the halves and
     * sorting each smaller list in the process
     */ 
    cout << "\nThis program sorts a given array via merge sort.\n" << endl;
    int len;
    cout << "Enter length of array : ";
    cin >> len;

    vector<int> arr(len);

    cout << "Enter space seperated elements of array," << endl;
    for (int i = 0; i < len; i += 1) cin >> arr[i];

    merge(arr, 0, len - 1);

    cout << "\nThe sorted array is," << endl;
    for (int i = 0; i < len; i += 1) {
        cout << arr[i];
        if (i == len - 1) cout << endl;
        else cout << ", ";
    }

    cout << endl;

    return 0;
}

void merge(vector<int> &arr, int start, int end) {
    // We need to divide into two halves
    int mid = (start + end) / 2;

    // Else the array has one element and is sorted
    if (start < end) {
        // Divide & Combine till we have one element left
        merge(arr, start, mid);
        merge(arr, mid + 1, end);

        recombine(arr, start, mid, end);
    }
}

void recombine(vector<int> &arr, int start, int mid, int end) {
    // Pointers to our array
    int i = start;
    int j = mid + 1;

    // We will keep the sorted elements here temporarily
    int k = 0;
    vector<int> temp(end - start + 1);

    // Sort and place into temp
    while (i <= mid && j <= end) {
        if (arr[i] < arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }

    // Left overs
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= end) temp[k++] = arr[j++];

    // Replace them into array
    for (int l = end; l >= start; l -= 1) arr[l] = temp[--k];
}