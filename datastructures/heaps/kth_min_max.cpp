#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int getKthLargest(vector<int> &, int);
int getKthSmallest(vector<int> &, int);

int main() {
    /**
     * In order to get the kth largest or smallest element in an
     * array, we can simply use a max heap or min heap, and conversely
     * pop elements k - 1 time, the resultant top of the heap will
     * give us the required smallest or largest element
     */ 
    cout << "\nThis program finds out the kth largest or smallest number in a list of numbers.\n" << endl;
    int n, kSm, kLg;
    cout << "Enter the number of elements to consider: ";
    cin >> n;
    cout << "Enter the value of k which indexes the smallest element: ";
    cin >> kSm;
    cout << "Enter the value of k which indexes the largest element: ";
    cin >> kLg;

    vector<int> elems(n);
    cout << "Enter space seperated elements of the array," << endl;
    for (int i = 0; i < n; i += 1) cin >> elems[i];

    int kthSmallest = getKthSmallest(elems, kSm);
    int kthLargest = getKthLargest(elems, kLg);

    cout << "\nThe " << kSm << "th smallest element is: " << kthSmallest << "." << endl;
    cout << "The " << kLg << "th largest element is: " << kthLargest << "." << endl;

    cout << endl;

    return 0;
}

int getKthSmallest(vector<int> &elems, int k) {
    // We will use minheap for getting smallest number, since
    // the smallest number is stored in the top for min Heap
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (auto &x : elems) minHeap.push(x);

    // We pop exactly k - 1 elements, so the next element in
    // top is the kth smallest element
    for (int i = 0; i < k - 1; i += 1) minHeap.pop();

    return minHeap.top();
}

int getKthLargest(vector<int> &elems, int k) {
    // We will use maxheap for getting largest number, since
    // the largest number is stored in the top for max Heap
    priority_queue<int, vector<int>, greater<int>> maxHeap;
    for (auto &x : elems) maxHeap.push(x);

    // We pop exactly k - 1 elements, so the next element in
    // top is the kth largest element
    for (int i = 0; i < k - 1; i += 1) maxHeap.pop();

    return maxHeap.top();
}
