#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int goodSetCount(vector<int> &, int);

int main() {
    /**
     * In order to find out the good set count of all elements of the list
     * we first sort the list, since every element must divide the next 
     * Then we simply add the count of how many numbers divide a certain 
     * number, to its next multiple, i.e if a certain element could be divided
     * `n` times, any multiple of that number will also be divisible `n` times
     */ 
    cout << "\nThis program finds out how many such subsets exist in an array, where every number divides the next.\n" << endl;
    int n;
    cout << "Enter the number of elements to consider: ";
    cin >> n;

    vector<int> elems(n);
    cout << "Enter space seperated elements of the list," << endl;
    for (int i = 0; i < n; i += 1) cin >> elems[i];

    int maximumElement = *max_element(elems.begin(), elems.end());

    int setCnt = goodSetCount(elems, maximumElement);

    cout << "\nThere exists " << setCnt << " such subsets in this array." << endl;

    cout << endl;

    return 0;
}

int goodSetCount(vector<int> &arr, int mxSize) {
    // Since we will be counting iteratively what elements gets
    // divided by the current element, we need a sorted array of elements
    // i.e. if 2 & 4 divides 8, 8 will divide 16, but so will 2 & 4 
    sort(arr.begin(), arr.end());

    // This will store how many times an element is divided by another
    vector<int> frequency(mxSize + 1, 0);

    // Every element divides itself, hence is a good set
    for (auto &x : arr) frequency[x] = 1;

    int ans = 0;

    for (auto &x : arr) {
        ans += frequency[x];

        for (int j = x + x; j <= mxSize; j += 1) {
            // If an element is not in array, we do not to 
            // count how many elements divide it
            if (frequency[j] == 0) continue;

            // If we could reach a certain element `n` times, we
            // also be including multiples of that element in that good set
            // hence we add the count of that element to each of its multiples
            frequency[j] += frequency[x];
        }
    }

    return ans;
}