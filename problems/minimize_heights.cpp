#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minimizeHeights(vector<int> &, int);

int main() {
    /**
     * In order to find the minimal difference we can simply
     * sort the array and then compare the minimal value
     * between the value at 0th + k & curr - k, the reverse
     * for maximum. Their minimal difference is the answer
     */ 
    cout << "\nThis problem finds out minimal differnce between max & min after adding / removing a certain value.\n" << endl;
    int n, k;
    cout << "Enter the length of the heights list: ";
    cin >> n;
    cout << "Enter margin of height modification: ";
    cin >> k;

    vector<int> heights(n);
    cout << "Enter space seperated heights of the list," << endl;
    for (int i = 0; i < n; i += 1) cin >> heights[i];

    int minimalDiff = minimizeHeights(heights, k);

    cout << "\nThe minimal difference between max & min after adjusting heights is: " << minimalDiff << "." << endl;

    cout << endl;

    return 0;
}

int minimizeHeights(vector<int> &heights, int k) {
    // We first sort it to keep lowest to left & highest to right
    sort(heights.begin(), heights.end());

    // This is starting difference we work with
    // assuming we add k to both of them
    int minimal = heights.back() - heights.front();

    for (int i = 1; i < heights.size(); i += 1) {
        // This will allow us to find the minimal possible value
        int alterMinima = min(heights[0] + k, heights[i] - k);
        // This will allow us to get maximal possible value
        int alterMaxima = max(heights[heights.size() - 1] - k, heights[i - 1] + k);
            
        // We do not consider negative heights of buildings
        if (alterMinima < 0 || alterMaxima < 0) continue;
            
        minimal = min(minimal, alterMaxima - alterMinima);
    }

    return minimal;
}