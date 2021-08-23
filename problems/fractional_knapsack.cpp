#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

double getGreedyKnapsack(vector<pair<int, int>> &, int, vector<int> &);

int main() {
    /**
     * In order to select items with maximal value in a constrained
     * space, we will simply divide each item's value with its own
     * weight, then sort it in descending order. This would give
     * us the item which is worth more in a single unit weight
     */ 
    cout << "\nThis program finds out the maximum items we can take under a given capacity, which will maximize our profits, given items can be broken into parts.\n" << endl;
    int capacity, n;
    cout << "Enter capacity of bag to consider: ";
    cin >> capacity;
    cout << "Enter number of items to consider: ";
    cin >> n;

    vector<pair<int, int>> items(n);

    cout << "Enter space seperated weights to consider," << endl;
    for (int i = 0; i < n; i += 1) cin >> items[i].first;

    cout << "Enter space seperated profits for each of them," << endl;
    for (int i = 0; i < n; i += 1) cin >> items[i].second;

    vector<int> bag;

    double maxVal = getGreedyKnapsack(items, capacity, bag);

    cout << "\nThe maximum profit we can carry in our bag is: " << maxVal << "." << endl;
    cout << "The items we took, gave us weights of: ";
    for (auto &x : bag) cout << x << " ";

    cout << endl;

    return 0;
}

double getGreedyKnapsack(vector<pair<int, int>> &items, int capacity, vector<int> &bag) {
    // First we sort the items in descending order of value to weight ratio
    sort(items.begin(), items.end(), [](pair<int, int> &a, pair<int, int> &b) {
        // We find the ration of value to weight, i.e.
        // value in unit weight fraction of the item
        double itemA = (double)a.second / a.first;
        double itemB = (double)b.second / b.first;
        return itemA > itemB; 
    });

    int currWt = 0;
    double currProf = 0;

    for (int i = 0; i < items.size(); i += 1) {
        int weight = items[i].first;
        int value = items[i].second;

        if (currWt + weight <= capacity) {
            // If this item can fit wholly inside the bag
            // we stuff all of it into current variables
            currWt += weight;
            currProf += value;
            bag.push_back(weight);
        } else {
            // otherwise we only keep the fraction of value
            // we could fit inside
            currProf += (value * (capacity - currWt) / weight);
            currWt += capacity - currWt;
            bag.push_back(capacity - currWt);
        }
    }

    return currProf;
}