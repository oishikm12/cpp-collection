#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Element {
    public:
        // Custom class for complex data
        int val;
        // kPos represents the which array it is
        int kPos;
        // iPos represents the position in current array
        int iPos;

        Element(int v, int k, int i) : val(v), kPos(k), iPos(i) {}
};

class compareElem {
    public:
        // Custom comparator for Element Min Heap
        bool operator()(Element const& a, Element const& b) {
            // We want the heap to be a minHeap, i.e. ascending order
            return a.val > b.val;
        }
};

vector<int> mergeKArr(vector<vector<int>> &, int);

int main() {
    /**
     * In order to merge K sorted arrays via heap, we will use a 
     * Min Heap, and simpy insert the first element of every array
     * in this heap. For every iteration we will remove the topmost
     * element, and in its place insert an element from the same 
     * array that the topmost element belonged to
     */ 
    cout << "\nThis program merges K sorted arrays into one\n" << endl;
    int sz;
    cout << "Enter the number of arrays, and number of elements in each to consider: ";
    cin >> sz;

    vector<vector<int>> arr(sz, vector<int>(sz));
    cout << "Enter space seperated, line delimited elements of each array," << endl;
    for (int i = 0; i < sz; i += 1) for (int j = 0; j < sz; j += 1) cin >> arr[i][j];

    vector<int> combinedArr = mergeKArr(arr, sz);

    cout << "\nThe merged array is," << endl;
    for (int i = 0; i < combinedArr.size(); i += 1) {
        cout << combinedArr[i];
        if (i == combinedArr.size() - 1) cout << endl;
        else cout << ", ";
    }

    cout << endl;

    return 0;
}

vector<int> mergeKArr(vector<vector<int>> &arr, int k) {
    priority_queue<Element, vector<Element>, compareElem> minHeap;
    vector<int> ans;
    
    for (int i = 0; i < k; i += 1) {
        // First we insert the first element from every 
        // array in the list
        minHeap.push(Element(arr[i][0], i, 0));
    }
    
    while (!minHeap.empty()) {
        // We then pop the topmost, ie. smallest element
        // insert it into the resultant array, and then
        // insert the next element from the array which
        // the popped element belonged to
        Element curr = minHeap.top();
        minHeap.pop();
        
        ans.push_back(curr.val);
        
        if (curr.iPos + 1 == k) continue;
        
        minHeap.push(Element(arr[curr.kPos][curr.iPos + 1], curr.kPos, curr.iPos + 1));
    }
    
    return ans;
}