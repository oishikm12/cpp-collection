#include <iostream>
#include <vector>
using namespace std;

int findTouches(int, int, vector<string> &, vector<vector<int>> &);

int main() {
    /**
     * In order to find out how many uniques exist at any given stage
     * we will be using a bit mask and consequent recursion, if at any
     * time, the mask turns out to be a power of 2, it signifies that
     * we could uniquely distinguish 2 strings
     */
    cout << "\nThis program finds out the number of touches required to tell all strings apart from each other.\n" << endl; 
    int n;
    cout << "Enter the number of strings to consider: ";
    cin >> n;

    vector<string> strings(n);
    cout << "Enter line delimited binary strings," << endl;
    for (int i = 0; i < n; i += 1) cin >> strings[i];

    vector<vector<int>> store(strings[0].size(), vector<int>(1 << (n + 1), -1));
    int touches = findTouches(strings[0].size() - 1, (1 << n) - 1, strings, store);

    cout << "\n" << touches << " touches will be needed to tell all the strings apart." << endl;

    cout << endl;

    return 0;
}

int findTouches(int pos, int mask, vector<string> &strings, vector<vector<int>> &store) {
    // Mask has reached its final value, so it is power of 2
    // i.e. all bits except 1 is 0
    if ((mask & (mask - 1)) == 0) return 0;

    // Max value for invalid position
    if (pos < 0) return 1e5;

    // Overlapping Subproblem
    if (store[pos][mask] != -1) return store[pos][mask];

    int newMask1 = 0, newMask2 = 0;
    int touches = 0;

    for (int i = 0; i < strings.size(); i += 1) {
        // If we have not differentiated between this position of the string
        if (mask & (1 << i)) {
            // It took us 1 touch to differentiate
            touches += 1;

            // Seperate masks to differentiate between 1s & 0s
            if (strings[i][pos] == '0') newMask1 = newMask1 | (1 << i);
            else newMask2 = newMask2 | (1 << i);
        }
    }

    // We compare costs if we were to compare current, and if we dont compare current
    int incCurr = findTouches(pos - 1, newMask1, strings, store) + findTouches(pos - 1, newMask2, strings, store) + touches;
    int exCurr = findTouches(pos - 1, mask, strings, store);

    store[pos][mask] = min(incCurr, exCurr);

    return store[pos][mask];
}
