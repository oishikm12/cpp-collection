#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int getMaxSubSum(vector<int> &, int);

int main() {
    /**
     * In order to find the kth largest possible subarray sum, we will
     * maintain a minHeap of all possible subarray sums. By restricting 
     * the size of this heap to k, and only inserting greater elements
     * we can get the kth largest sum in the top
     */
    cout << "\nThis program finds out the kth largest possible subarray sum from a given array.\n" << endl; 
    int n, k;
    cout << "Enter the size of the array to consider: ";
    cin >> n;
    cout << "Enter the value of k which indexes the largest sum: ";
    cin >> k;

    vector<int> elems(n);
    cout << "Enter space seperated elements of the array," << endl;
    for (int i = 0; i < n; i += 1) cin >> elems[i];

    int maxSum = getMaxSubSum(elems, k);

    cout << "\nThe "<< k << "th largest possible subarray sum is: " << maxSum << "." << endl;

    cout << endl;

    return 0;
}

int getMaxSubSum(vector<int> &elems, int k) {
    int n = elems.size();

    // We will maintain this minheap of size k, that way
    // we can selectively insert only elements greater
    // than top into the heap. In the end we will be left
    // with the kth largest to the top (since itll be the
    // smallest one in the min heap)
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    // Instead of finding all possible contigious subarray
    // sum, we can simply find the cumulative sum, wherein
    // subtracting any two indices will give us the cumulative
    // sum for that specific subarray
    vector<int> cumSum(n + 1);
    cumSum[0] = 0;
    cumSum[1] = elems[0];

    for (int i = 2; i <= n; i += 1) cumSum[i] = cumSum[i - 1] + elems[i - 1];

    for (int i = 1; i <= n; i += 1) {
        for (int j = i; j <= n; j += 1) {
            // Calculates contigious subarray sum from position
            // [i - 1] to [j]
            int subArrSum = cumSum[j] - cumSum[i - 1];

            if (minHeap.size() < k) minHeap.push(subArrSum);
            else if (minHeap.top() < subArrSum) {
                // We found an element greater than the current
                // smalles, hence we swap out the current
                // smalest, this way the minHeap will maintian
                // k greatest sorted in ascending
                minHeap.pop();
                minHeap.push(subArrSum);
            }
        }
    }

    return minHeap.top();
}