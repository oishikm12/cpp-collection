#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

bool hasZeroSum(vector<int> &);

int main() {
    /**
     * In order to find wether a certain subarray sum equals 0
     * or not, all we have to do is find the prefix sum, i.e. 
     * cumulative sum of the array, if any number is repeated in
     * this array, that would signify that an equivalent substraction
     * to an addition exists, i.e. we can reach 0 with the set
     */ 
    cout << "\nThis program finds out if there exists a subarray whose sum equals to zero.\n" << endl;
    int n;
    cout << "Enter the number of elements to consider: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter space seperated elements of the array," << endl;
    for (int i = 0; i < n; i += 1) cin >> arr[i];

    bool zero = hasZeroSum(arr);

    if (zero) cout << "\nThe array has a subarray whose sum equals 0." << endl;
    else cout << "\nNo subarray exists whose sum is equal to 0." << endl;

    cout << endl;

    return 0;
}

bool hasZeroSum(vector<int> &arr) {
    // This will store all unique prefix sums, as such
    // we can find if any prefix sum has already appeared
    unordered_set<int> cnt;
        
    // We inserted current element as 0 first, since selecting
    // no element gives us that
    int curr = 0;
    cnt.insert(curr);
    
    for (int i = 0; i < arr.size(); i += 1) {
        curr += arr[i];
        
        // If a sum is repeated, we found a subarray which
        // would result in 0, i.e. a suitable +ve & -ve number
        if (cnt.count(curr) == 1) return true;
        else cnt.insert(curr);
    }
    
    return false;
}