#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    /**
     * Rainwater Harvesting is a problem where you are given a set of numbers
     * in a array each representing height of buildings in order. Whenever a 
     * short building between two tall ones is present, it harvest rainwater.
     * A simple way to solve how much water can be stored is to find out the
     * max height of it's left & right buildings and whichever is minimum, is 
     * the amount of water that can be harvested
     */
    cout << "\nThis program calculates rainwater harvesting.\n" << endl;
    int len;
    cout << "Enter number of buildings to consider : ";
    cin >> len;

    vector<int> arr(len), left(len), right(len);

    cout << "Enter space seperated heights of each building," << endl;
    for (int i = 0; i < len; i += 1) cin >> arr[i];

    for (int i = 0; i < len; i += 1) {
        // The reason why max is stored is because water will flow to the
        // minimum upper limit, however there can be building with intermediate
        // height in the middle. eg - 7 6 [4] 7 => water flows till 7 to left
        left[i] = i == 0 ? arr[i] : max(left[i - 1], arr[i]);
        right[len - i - 1] = i == 0 ? arr[len - i - 1] : max(arr[len - i - 1], right[len - i]);
    }

    int total = 0;
    for (int i = 0; i < len; i += 1) {
        // The main logic being the water that can be stored is minimum height
        // of left or right - height of current building
        int val = min(left[i], right[i]) - arr[i];
        // Should this be -ve we simply wanna ignore
        if (val < 0) val = 0;
        else total += val;
    }

    cout << "The amount of water that can be stored is : " << total << endl;
    cout << endl;

    return 0;
}