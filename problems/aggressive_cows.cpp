#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isPossible(vector<int> &, int, int);

int main() {
    /**
     * In order to find out the stall placement with maximum distance
     * we use binary search to find out distances till stalls are and
     * all cows can be placed
     */ 
    cout << "\nThis problem places cows in their stalls at max possible distance from each other\n" << endl;
    int n, cows;
    cout << "Enter the number of stalls: ";
    cin >> n;
    cout << "Enter number of cows to place: ";
    cin >> cows;

    vector<int> stalls(n);
    cout << "\nEnter space seperated positions of stalls." << endl;
    for (int i = 0; i < n; i += 1) cin >> stalls[i];

    // We need to sort if we are to use binary search
    sort(stalls.begin(), stalls.end());

    int minDist = 0;
    
    // We set low to 0 such that each cow may be placed in the same
    // stall and high as max distance such that only 2 cows can stay
    int low = 0;
    int high = stalls[n - 1] - stalls[0];
    int mid;

    while (high >= low) {
        mid = (high + low) / 2;

        if (isPossible(stalls, cows, mid)) {
            low = mid + 1;
            minDist = mid;
        } else {
            high = mid - 1;
        }
    }

    cout << "\nCows can be placed at a least distance of " << mid << "." << endl;

    cout << endl;

    return 0;
}

bool isPossible(vector<int> &stalls, int cows, int dist) {
    // We consider the first cow to always be present in first stall
    int placed = 1;
    int last = stalls[0];

    // We then place each cow at the next stall if the minimum
    // distance b/w them is at least `dist`
    for (int i = 1; i < stalls.size(); i += 1) {
        if ((stalls[i] - last) >= dist) {
            placed += 1;
            // We have placed all cows so we return
            if (placed == cows) return true;

            last = stalls[i];
        }
    }

    // If we reach this point it signifies that
    // not all cows could be placed
    return false;
}