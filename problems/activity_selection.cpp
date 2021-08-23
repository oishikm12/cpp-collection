#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int getMaxActivityCount(vector<pair<int, int>> &, int);

int main() {
    /**
     * In order to find out the maximum number of activites
     * that can be completed in one day, we need to simply 
     * sort the activities based on their ending time. Any 
     * activity that can be completed before start of next
     * can therefore be included in this list
     */ 
    cout << "\nThis program finds out the maximum number of activities possible in a given time frame.\n" << endl;
    int n;
    cout << "Enter the total number of activities to consider: ";
    cin >> n;

    vector<pair<int, int>> duration(n);
    cout << "Enter space seperated starting and ending time of an activity, line delimited for all activities," << endl; 
    for (int i = 0; i < n; i += 1) cin >> duration[i].first >> duration[i].second;

    int acCount = getMaxActivityCount(duration, n);

    cout << "\nWe can perform at most " << acCount << " activities out of " << n << "." << endl;

    cout << endl;

    return 0;
}

int getMaxActivityCount(vector<pair<int, int>> &duration, int n) {
    // First we need to sort the durations on ascending
    // order of their ending times
    sort(duration.begin(), duration.end(), [](pair<int, int> &a, pair<int, int> &b) {
        return a.second < b.second;
    });

    int cnt = 1;
    int currEnding = duration[0].second;

    for (int i = 1; i < n; i += 1) {
        auto &[start, end] = duration[i];

        // If this activity starts after the previous ends
        // we can perform this activity also
        if (start >= currEnding) {
            cnt += 1;
            currEnding = end;
        }
    }

    return cnt;
}