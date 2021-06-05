#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

string minimalSum(vector<int> &, int);

int main() {
    /**
     * In order to add rearranged orders of the digits together such
     * that the sum is minimal, we will use a Max Heap to maintain
     * what digits to be added at each step. In the end the reversed
     * string will give us the desired sum
     */ 
    cout << "\nThis program constructs two numbers from a list of digits such that their sum is minimal.\n" << endl;
    int n;
    cout << "Enter the number of digits to consider: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter space seperated digits to consider," << endl;
    for (int i = 0; i < n; i += 1) cin >> arr[i];

    string res = minimalSum(arr, n);

    cout << "\nThe minimal possible sum of two numbers formed from the array is: " << res << "." << endl;

    cout << endl;

    return 0; 
}

string minimalSum(vector<int> &arr, int n) {
    // Since a max Heap maintains the maximal element to the top, we
    // will add the largest and second largest at every step, and 
    // append the resultant to a string
    priority_queue<int> maxHeap;
        
    for (int i = 0; i < n; i += 1) maxHeap.push(arr[i]);
    
    string res;
    // We need to maintain the carry at each step, this
    // is the reason we start from largest & not smallest numbers
    int carry = 0;
    
    while (!maxHeap.empty()) {
        int curr = carry;
        
        curr += maxHeap.top();
        maxHeap.pop();
        
        if (!maxHeap.empty()) {
            curr += maxHeap.top();
            maxHeap.pop();
        }
        
        if (curr) {
            // We do not want to append the numbers if they
            // are not value but just 0 carry
            carry = curr / 10;
            curr = curr % 10;
        
            res.push_back('0' + curr);
        }
    }
    
    if (carry) res.push_back('0' + carry);
    
    // For the sum to be minimal we need to add maximal elements 
    // near units place and minimal elements farthest from units
    // place. However with proper ordering we cannot manage carry
    // hence the reversal
    reverse(res.begin(), res.end());
    
    return res;
}
