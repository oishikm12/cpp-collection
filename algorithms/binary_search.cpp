#include <iostream>
#include <vector>
using namespace std;

int search(vector<int>&, int, int);

int main() {
    /**
     * Binary search, searches for an element in log n time by continiously,
     * partitioning a sorted list into two equal halves & considering only
     * the half where the element is likely to be, this process is then 
     * repeated till we either find it or the list can't be partitioned 
     */ 
    cout << "\nThis program seacrhes for a certain element via binary search.\n" << endl;
    int len;
    cout << "Enter length of array : ";
    cin >> len;
    
    vector<int> arr(len);

    cout << "Enter space seperated elements of the sorted array," << endl;
    for (int i = 0; i < len; i += 1) cin >> arr[i];

    int key;
    cout << "Enter the element you would like to search for : ";
    cin >> key;

    int found = search(arr, len, key);

    if (found == -1) {
        cout << "\nUnfortunately, we could not find the element." << endl;
    } else {
        cout << "The element " << key << " was found at index " << found << "." << endl;
    }

    cout << endl;

    return 0;
}

int search(vector<int> &arr, int len, int key) {
    // We do not actualy perform partitioning, we just set up range limits for
    // our convinience. We then consider the middle element inside that range
    // depending on if our element is smaller or greater than the middle elem
    // Accordingly, we re-draw our partition
    int low = 0;
    int high = len;
    int mid;

    while (high > low) {
        mid = (high + low) / 2;

        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }

    return -1;
}