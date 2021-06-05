#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Element {
    public:
        // Custom class for complex data
        int val;
        // iPos represents the position in arrays of arrays
        int iPos;
        // jPos represents the position in current array
        int jPos;

        Element(int v, int i, int j) : val(v), iPos(i), jPos(j) {}
};

class compareElem {
    public:
        // Custom comparator for Element Min Heap
        bool operator()(Element const& a, Element const& b) {
            // We want the heap to be a minHeap, i.e. ascending order
            return a.val > b.val;
        }
};

pair<int, int> smallestRange(vector<vector<int>> &);

int main() {
    /**
     * In order for us to find out the perfect range for arrays,
     * we will be maintaining a minHeap of the same size as the 
     * arrays, thereby the difference between the minimal element
     * and the maximal element encountered till then will give
     * us the required range
     */ 
    cout << "\nThis program finds out the minimal range among multiple sorted arrays, such that at least one element from each array.\n" << endl;
    int n;
    cout << "Enter the number of arrays and elements in each to consider: ";
    cin >> n;

    vector<vector<int>> arr(n, vector<int>(n));
    cout << "Enter space seperated line delimited elements of each arrays," << endl;
    for (int i = 0; i < n; i += 1) for (int j = 0; j < n; j += 1) cin >> arr[i][j];

    pair<int, int> range = smallestRange(arr);

    cout << "\nThe minimal range including elements from all arrays is from " << range.first << " to " << range.second << "." << endl;

    cout << endl;

    return 0;
}

pair<int, int> smallestRange(vector<vector<int>> &arr) {
    priority_queue<Element, vector<Element>, compareElem> minHeap;
    int k = arr.size();   

    // Create a min heap with k heap nodes. Every heap node
    // has first element of an list
    int maxEl = INT_MIN;
    for(int i = 0; i < k; i++) {
        minHeap.push(Element(arr[i][0], i, 0));
        maxEl = max(maxEl, arr[i][0]);
    }

    // Initial Range from l to h
    int low = minHeap.top().val;
    int high = maxEl;

    while(!minHeap.empty()) {
        // Minimum node from the minHeap
        Element curr = minHeap.top();
        minHeap.pop();                                    

        // Increment the current j index to move to next 
        // element of the list
        int i = curr.iPos; 
        int j = curr.jPos + 1;        
        
        // If we reach the end of any one list then we break
        if(j == arr[i].size()) break;                                    

        minHeap.push(Element(arr[i][j], i, j));

        // Update the max element            
        maxEl = max(maxEl, arr[i][j]);
        // update the smallest range
        int range = maxEl - minHeap.top().val;    

        if(high - low > range) {
            low = minHeap.top().val;
            high = maxEl;
        }
    }

    return make_pair(low, high);
}