#include <iostream>
#include <vector>
using namespace std;

int getKnapsackValue(vector<int> &, vector<int> &, int, vector<int> &);

int main() {
    /**
     * In order to find out what weight to place to maximize profit
     * we will simply compare between wether the profit is greater if
     * we had not placed the current item, or if it is greater if
     * we consider the value of the current item, added to whatever 
     * profit we have after removing items to make space for the current
     */ 
    cout << "\nThis program finds out the maximum items we can take under a given capacity, which will maximize our profits.\n" << endl;
    int capacity, n;
    cout << "Enter capacity of bag to consider: ";
    cin >> capacity;
    cout << "Enter number of items to consider: ";
    cin >> n;

    vector<int> weights(n), profits(n);

    cout << "Enter space seperated weights to consider," << endl;
    for (int i = 0; i < n; i += 1) cin >> weights[i];

    cout << "Enter space seperated profits for each of them," << endl;
    for (int i = 0; i < n; i += 1) cin >> profits[i];

    vector<int> items;

    int maxVal = getKnapsackValue(weights, profits, capacity, items);

    cout << "\nThe maximum profit we can carry in our bag is: " << maxVal << "." << endl;
    cout << "The items we took, gave us weights of: ";
    for (auto &x : items) cout << x << " ";

    cout << endl;

    return 0;
}

int getKnapsackValue(vector<int> &weights, vector<int> &profits, int cap, vector<int> &items) {
    int sz = weights.size();
    vector<vector<int>> knapsack(sz + 1, vector<int>(cap + 1, 0));

    for (int i = 1; i <= sz; i += 1) {
        for (int j = 1; j <= cap; j += 1) {
            // At any given time, i represents the item we
            // want to add, and j represents the current capacity
            if (weights[i - 1] <= j) {
                // This item can now be accomodated
                int profitWithoutCurrent = knapsack[i - 1][j];
                int profitWithCurrent = knapsack[i - 1][j - weights[i - 1]] + profits[i - 1];
                knapsack[i][j] = max(profitWithCurrent, profitWithoutCurrent);
            } else {
                // Current item cannot be added yet, no space
                knapsack[i][j] = knapsack[i - 1][j];
            }
        }
    }

    int wt = cap;
    int res = knapsack[sz][cap];
    
    for (int i = sz; i > 0 && res > 0; i -= 1) {
        if (res == knapsack[i - 1][wt]) continue;
      	else {
         	items.push_back(weights[i - 1]);
         	res -= profits[i - 1];
         	wt -= weights[i - 1];
      	}
    }

    return knapsack[sz][cap];
}