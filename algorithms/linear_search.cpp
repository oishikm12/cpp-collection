#include <iostream>
#include <vector>
using namespace std;

int search(vector<int>&, int, int);

int main() {
    /**
     * Linear Search iterates over ach element in a array and compares them
     * with key to return if found
     */ 
    cout << "\nThis program seacrhes for a certain element via linear search.\n" << endl;
    int len;
    cout << "Enter length of array : ";
    cin >> len;
    
    vector<int> arr(len);

    cout << "Enter space seperated elements of the array," << endl;
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
    // We simply return from loop if found
    for (int i = 0; i < len; i += 1) {
        if (arr[i] == key) return i;
    }

    return -1;
}