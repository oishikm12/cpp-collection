#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int getAPCount(vector<int> &);

int main() {
    /**
     * In order to get all counts of an AP, we will simply maintain
     * a map of elements starting from each index, that way whenever
     * a new element appears at a certain distance we can simply
     * inherit the distance from the previous & add 1 to it
     */ 
    cout << "\nThis program finds out the number of arithmetic progressions in a sequence.\n" << endl;
    int n;
    cout << "Enter the number of elements to consider: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter space seperated elements of the sequence," << endl;
    for (int i = 0; i < n; i += 1) cin >> arr[i];

    int aps = getAPCount(arr);

    cout << "There are " << aps << " no. of possible AP in this sequence." << endl;

    cout << endl;

    return 0;
}

int getAPCount(vector<int> &arr) {
    int n = arr.size();

    // Every element as well as an empty sequence is in itself an AP
    int count = n + 1;

    vector<unordered_map<int, int>> store(n);

    for (int i = 0; i < n - 1; i += 1) {
        for (int j = i + 1; j < n; j += 1) {
            // A possible arithmetic progression is formed by 
            // comparing every element with every element after it
            int diff = arr[j] - arr[i];
            // For every element at certain distance
            store[i][diff] += 1;
            count += 1;
        }
    }

    for (int i = n - 3; i >= 0; i -= 1) {
        // We need to start from 2nd last element
        // since last element cannot form a AP sequence
        for (int j = i + 1; j < n; j += 1) {
            int diff = arr[j] - arr[i];
            // Two elements with same AP diff, can be added
            store[i][diff] = store[i][diff] + store[j][diff];
            // We need to only store the count of traversal
            count += store[j][diff];
        }
    }

    return count;
} 
