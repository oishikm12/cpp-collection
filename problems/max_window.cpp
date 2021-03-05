#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int main() {
    /**
     * We use a deque as a sliding window to keep track of maximum element at
     * each stage of traversal. We do this by comparing the elements already in
     * queue with the newest element and checking if the element is greater or
     * smaller. Elements going out of range or smaller are popped
     */
    cout << "\nThis problem finds out maximum in a given range over all possible subarrays.\n" << endl;
    int len, size;
    cout << "\nEnter number of elements to consider : ";
    cin >> len;
    cout << "\nEnter size of window to consider : ";
    cin >> size;

    vector<int> elems(len);
    cout << "\nEnter space seperated elements of list." << endl;
    for (int i = 0; i < len; i += 1) cin >> elems[i];

    deque<int> window(size);

    // first size elements are processed first
    for (int i = 0; i < size; i += 1) {
        while (!window.empty() && elems[i] > elems[window.back()]) window.pop_back();
        window.push_back(i);
    }

    cout << "\nThe max element in each window is : " << endl;

    // processing the rest of the elements
    for (int i = size; i < len; i += 1) {
        // print the current largest
        cout << elems[window.front()] << " ";

        // remove elements from previous window
        while (!window.empty() && window.front() <= (i - size)) window.pop_front();
        // remove elements lesser than current max
        while (!window.empty() && elems[i] >= elems[window.back()]) window.pop_back();
        // add new element
        window.push_back(i);
    }

    // the last element
    cout << elems[window.front()] << endl;

    cout << endl;
    
    return 0;
}
