#include <iostream>
#include <vector>
using namespace std;

int getCandyDist(int, int, int, vector<vector<int>> &, vector<int> &);

int main() {
    /**
     * In order to find out all possible arrangements of candies
     * we will use recursion, and to check wether the the current 
     * person likes the candy or not, we will use a bitmask.
     */
    cout << "\nThis program finds out all possible candy distributions schemes, where certain people like certain candies.\n" << endl; 
    int n;
    cout << "Enter the number of candies & students to consider: ";
    cin >> n;

    vector<vector<int>> preference(n, vector<int>(n));
    cout << "Enter space sepereated preferences of a candy, for all users delimted by newline," << endl;
    for (int i = 0; i < n; i += 1) for (int j = 0; j < n; j += 1) cin >> preference[i][j];

    // If there are n students to consider, there are 2^n possiblities
    vector<int> store(1 << n, -1);

    int configs = getCandyDist(0, n, 0, preference, store);

    cout << "\nThere are " << configs << " possible ways to distribute the candies respecting preferences." << endl;

    cout << endl;

    return 0;
}

int getCandyDist(int currPerson, int totalPeople, int mask, vector<vector<int>> &preference, vector<int> &store) {
    // We have distributed candy to all people, hence a successful distribution
    if (currPerson == totalPeople) return 1;

    // We already found out this configuration
    if (store[mask] != -1) return store[mask];

    // Storing cumulative arrangements for all masks
    int configs = 0;

    for (int candy = 0; candy < totalPeople; candy += 1) {
        // We check if we are supposed to give a candy to this
        // certain person & if that person prefers the candy type
        if (!(mask & (1 << candy)) && preference[currPerson][candy] == 1) {
            configs += getCandyDist(currPerson + 1, totalPeople, mask | (1 << candy), preference, store);
        }
    }

    store[mask] = configs;

    return store[mask];
}