#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int pointsPossible(vector<int> &);

int main() {
    /**
     * In order to find out which number to select, we simply
     * have to find out the max of num * freq, and do this
     * every turn. Since when selecting a number, only 1 
     * instance of it gets deleted, a number which appears
     * multiple times will yield maximum point
     */ 
    cout << "\nThis problem finds out the maximum points one gets, if selecting a point destroys point next & prev to it in value.\n" << endl;
    int n;
    cout << "Enter the number of elements in the table: ";
    cin >> n;

    vector<int> table(n);
    cout << "Enter space seperated scores in the table," << endl;
    for (int i = 0; i < n; i += 1) cin >> table[i];

    int maxPoints = pointsPossible(table);

    cout << "\n" << maxPoints << " is the maximum possible points." << endl;

    cout << endl;

    return 0;
}

int pointsPossible(vector<int> &table) {
    int n = *max_element(table.begin(), table.end());
    vector<int> dp(n + 1);

    // Since deleting a number only deletes its next & prev
    // we need to keep track of missing elements in between
    // Also this allows us to keep track of frequency * num
    for (auto &x : table) dp[x] += x;

    dp[1] = max(dp[0], dp[1]);

    // For each step we simply check if it is more profitable
    // to delete current element & lose previous, or select
    // previous & lose the current
    // NOTE: In case of selecting current, we need to add prev
    // before prev, if any
    for (int i = 2; i <= n; i += 1) {
        dp[i] = max(dp[i - 1], dp[i - 2] + dp[i]);
    }

    return dp[n];
}