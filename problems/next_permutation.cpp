#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void nextPermutation(vector<int> &);

int main() {
    /**
     * In order to find the next permutation of a sequence of numbers,
     * we need to find the first ascending sequene from the end, and
     * simply reverse this sequence to get the lexgraphically greater no.
     */ 
    cout << "\nThis program finds the next lexographically greater permutation of a list of numbers.\n" << endl; 
    int n;
    cout << "Enter the number of items to consider: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter space seperated numbers to find next permutation of," << endl;
    for (int i = 0; i < n; i += 1) cin >> nums[i];

    nextPermutation(nums);

    cout << "\nThe lexographically greater permutation of the array is," << endl;
    for (int i = 0; i < n; i += 1) {
        cout << nums[i];
        if (i != n - 1) cout << " ";
    }

    cout << endl << endl;

    return 0;
}

void nextPermutation(vector<int> &nums) {
    int n = nums.size(), k, l;

    int i;
    // Find the largest index k such that nums[k] < nums[k + 1]
    for (i = n - 2; i >= 0; i--) {
        if (nums[i] < nums[i + 1]) break;
    }

    // If no such index exists, just reverse nums and done.
    if (i < 0) {
        reverse(nums.begin(), nums.end());
    } else {
        // Next Permutation can found by
        // a. Finding the largest index l > k such that nums[k] < nums[l].
        // b. Swapping nums[k] and nums[l].
        // c. Reversing the sub-array nums[k + 1:].
        for (l = n - 1; l > i; l--) {
            if (nums[l] > nums[i]) {
                break;
            }
        } 
        swap(nums[i], nums[l]);
        reverse(nums.begin() + i + 1, nums.end());
    }
}
