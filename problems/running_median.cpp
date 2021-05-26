#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    /**
     * In order to maintain a sorted order of elements, we will
     * maintain a min heap and a max heap simultaneously while
     * reading the numbers. If we maintain an equal number of 
     * elements in both the heaps, their respective tops will
     * give us the required median
     */ 
    cout << "\nThis program finds out the median after insertion of every element.\n" << endl;
    int n;
    cout << "Enter the number of elements to consider: ";
    cin >> n;

    vector<int> elems(n);

    cout << "Enter space seperated elements present in the list," << endl;
    for (int i = 0; i < n; i += 1) cin >> elems[i];

    // We will maintain both heaps to keep a sorted
    // track of what element is at the middle
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;

    cout << endl;

    for (auto &x : elems) {
        // If the maxheap is empty we just insert there
        if (maxHeap.empty()) maxHeap.push(x);
        else {
            // If the element is smaller than middle, we push it
            // to the left, i.e. maxHeap else it goes to right
            // i.e. minHeap
            if (x < maxHeap.top()) maxHeap.push(x);
            else minHeap.push(x);
        }

        int maxSize = maxHeap.size();
        int minSize = minHeap.size();
        int diff = maxSize - minSize;

        // If the diff between both heaps is greater than 1 node
        // that means we have to rebalance the nodes, since there
        // should be equal no. of elements before & after mid to
        // find the value of median
        if (diff > 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (diff < -1) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }

        cout << "The median after insertion of " << x << " is: ";

        if (maxHeap.size() == minHeap.size()) {
            // If there are equal nos, this signifies, even no.
            // of elements, hence median is avg. of center elements
            cout << (double)(maxHeap.top() + minHeap.top()) / 2 << "." << endl;
        } else {
            // If there are unequal nodes, then whichever has greater
            // count, it's top becomes the median value
            if (maxHeap.size() > minHeap.size()) cout << maxHeap.top() << "." << endl;
            else cout << minHeap.top() << "." << endl;
        }
    }

    cout << endl;

    return 0;
}