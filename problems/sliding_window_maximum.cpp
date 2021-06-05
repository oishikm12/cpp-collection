#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> windowLargest(vector<int> &, int);

int main() {
    /**
     * In order to find the largest element at all times in a sliding
     * window, we will maintain a max heap storing the inserted element
     * and its index as a pair. At any given time if the index of the 
     * topmost element is less than k elements behind current, we remove
     * it. The topmost element otherwise is the largest
     */ 
    cout << "\nThis program finds out the largest element in a sliding window over a list of elements.\n" << endl;
    int n, k;
    cout << "Enter the number of elements to consider: ";
    cin >> n;
    cout << "Enter size of the window to consider: ";
    cin >> k;

    vector<int> nums(n);
    cout << "Enter space seperated elements of the list," << endl;
    for (int i = 0; i < n; i += 1) cin >> nums[i];

    vector<int> result = windowLargest(nums, k);

    cout << "\nMaximum during each window traversal is:" << endl;
    for (int i = 0; i < n - k + 1; i += 1) {
        cout << "Maximum between " << nums[i] << " and " << nums[i + k - 1] << " is " << result[i] << "." << endl;
    }

    cout << endl;

    return 0;
}

vector<int> windowLargest(vector<int> &nums, int winSize) {
    // We simply maintain a max heap keeping in pairs
    // the number itself, and its index in the list
    priority_queue<pair<int, int>> heap;
    vector<int> ans;

    // The first k - 1 elements can be inserted simply because 
    // the window is not complete yet
    for (int i = 0; i < winSize - 1; i += 1) heap.push(make_pair(nums[i], i));

    for (int i = winSize - 1; i < nums.size(); i += 1) {
        // We must ensure that the largest element we are considering
        // is at most k - 1 distance away from current. Hence for all
        // which is more than k distance away, we simply remove them
        while (!heap.empty() && (i - heap.top().second) >= winSize) heap.pop();
    
        // We push the current element into the heap
        heap.push(make_pair(nums[i], i));

        // Then we simply push the largest element in current range into
        // our resultant vector
        ans.push_back(heap.top().first);
    }

    return ans;
}