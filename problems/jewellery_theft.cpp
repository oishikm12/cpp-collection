#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int getStolenItems(vector<pair<int, int>> &, vector<int> &);

int main() {
    /**
     * In order to get the maximum jewels that can be stolen
     * by a theif with limited number of bags, we sort the 
     * jewels in descending order of values, and the ascending
     * weights for capacity. Then we simply select the lower
     * bound for each jewel to get the best fit bag for it
     */
    cout << "\nThis program finds out how many jewels can be stolen by a theif.\n" << endl; 
    int n, k;
    cout << "Enter number of jewelleries to consider: ";
    cin >> n;
    cout << "Enter number of bags the theif has: ";
    cin >> k;

    vector<pair<int, int>> jewels(n);
    vector<int> bags(k);

    cout << "Enter space seperated value & weight of jewels delimited by newline," << endl;
    for (int i = 0; i < n; i += 1) cin >> jewels[i].first >> jewels[i].second;

    cout << "Enter space seperated capacity of each bag," << endl;
    for (int i = 0; i < k; i += 1) cin >> bags[i];

    int maxVal = getStolenItems(jewels, bags);

    cout << "\nWe can steal atmost jewlelleries worth " << maxVal << " in " << k << " bags." << endl;

    cout << endl;

    return 0;
}

int getStolenItems(vector<pair<int, int>> &jewels, vector<int> &bags) {
    // We first sort the items on descending order of value
    // and if they have same value, then increasing order of weight
    sort(jewels.begin(), jewels.end(), [](pair<int, int> &a, pair<int, int> &b) {
        if (a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    });

    // We will use a multi-set to store all the capacities of bags
    // we are considering in increasing order of weight
    multiset<int> store;
    for (auto &x : bags) store.insert(x);

    int ans = 0;

    for (auto &[value, weight] : jewels) {
        // There are no more bags remaining
        if (store.empty()) break;

        // We check the bag which can just contain the weight of
        // the current jewel
        auto exists = store.lower_bound(weight);

        if (exists != store.end()) {
            // We add this to our bag, and remove it from the jewellery store
            ans += value;
            store.erase(exists);
        }
    }

    return ans;
}
