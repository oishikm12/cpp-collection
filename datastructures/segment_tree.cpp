#include <iostream>
#include <vector>
using namespace std;

/**
 * Segment Tree is a data structure which is based on trees and
 * allows us range based queries in logarithmic time, by precalculating
 * the sum or query of each of child nodes in parent nodes
 */ 

class SegTree {
    private:
        vector<int> arr;
        vector<int> tree;

    public:
        // Initializes the segment tree
        SegTree(vector<int> &);

        // Builds a segment Tree via recursion
        void buildTree(int, int, int = 1);

        // Updates a value at specific index
        void updateTree(int, int, int, int, int = 1);

        // Performs query on range
        int query(int, int, int, int, int = 1);
};

SegTree :: SegTree(vector<int> &elems) {
    // We allocate four times the size of the given array
    // The actual size is 2 * pow(2, ceil(log2(arr.size()))) - 1
    tree.resize(4 * elems.size(), 0);
    arr = elems;

    // Recursively build the tree
    buildTree(0, arr.size() - 1);
}

void SegTree :: buildTree(int startingNode, int endingNode, int currNode) {
    // Base Condition, i.e. when start and end match, we
    // want to place the element at this node
    if (startingNode == endingNode) {
        tree[currNode] = arr[startingNode];
        return;
    }

    int mid = (endingNode - startingNode) / 2 + startingNode;

    // For a complete binary tree, the children of a node are
    // present at 2 * curr for left & 2 * curr + 1 for right
    buildTree(startingNode, mid, 2 * currNode);
    buildTree(mid + 1, endingNode, 2 * currNode + 1);

    // We store the sum of children nodes at current node
    tree[currNode] = tree[2 * currNode] + tree[2 * currNode + 1];
}

void SegTree :: updateTree(int value, int index, int startingNode, int endingNode, int currNode) {
    // Invalid Range
    if (startingNode > endingNode) return;

    // Base Condition, i.e. when start and end match, we
    // want to replace this element itself
    if (startingNode == endingNode) {
        arr[index] = value;
        tree[currNode] = value;
        return;
    }

    int mid = (endingNode - startingNode) / 2 + startingNode;

    // If the index of element to update is greater
    // then we move to right subtree, i.e. 2 * n + 1
    // and if smaller then to left 2 * n itself
    if (index > mid) updateTree(value, index, mid + 1, endingNode, 2 * currNode + 1);
    else updateTree(value, index, startingNode, mid, 2 * currNode);

    // We store the sum of children nodes at current node
    tree[currNode] = tree[2 * currNode] + tree[2 * currNode + 1];
}

int SegTree :: query(int left, int right, int startingNode, int endingNode, int currNode) {
    // Invalid Range
    if (startingNode > endingNode) return 0;

    // Case when completely outiside given range [S, E] < L || R < [S, E]
    if (left > endingNode || right < startingNode) return 0;

    // Case when completely inside range L <= [S, E] <= R
    if (left <= startingNode && endingNode <= right) return tree[currNode];

    // Otherwise we will consider the range to be
    // partially present in both of its children
    // S <= L <= E || S <= R <= E
    int mid = (endingNode - startingNode) / 2 + startingNode;
    int part1 = query(left, right, startingNode, mid, 2 * currNode);
    int part2 = query(left, right, mid + 1, endingNode, 2 * currNode + 1);

    return part1 + part2;
}

int main() {
    /**
     * We generate an instance of segment tree class and perform operations
     */ 
    cout << "\nThis program generates a sample segment tree object to generate subarray sum.\n" << endl;
    int n;
    cout << "Enter number of elements to consider: ";
    cin >> n;

    vector<int> elems(n);
    cout << "Enter space seperated elements of the array to consider," << endl; 
    for (int i = 0; i < n; i += 1) cin >> elems[i];
    
    SegTree seg(elems);
    bool flag = true;

    while (flag) {
        cout << "\nEnter your choice:" << endl;
        cout << "1. Update element of array." << endl;
        cout << "2. Query a specific range." << endl;
        cout << "3. Exit." << endl;
        int choice;
        cin >> choice;

        // Variables for choices
        int idx1, idx2, val;

        switch (choice) {
            case 1:
                cout << "\nEnter index of element to update: ";
                cin >> idx1;
                cout << "\nEnter new value to consider: ";
                cin >> idx2;
                seg.updateTree(idx2, idx1, 0, n - 1);
                break;
            case 2:
                cout << "\nEnter starting range: ";
                cin >> idx1;
                cout << "\nEnter ending range: ";
                cin >> idx2;
                val = seg.query(idx1, idx2, 0, n - 1);
                cout << "\nThe sum from " << idx1 << " to " << idx2 << " is " << val << "." << endl;
                break;
            case 3:
                cout << "\nGoodbye !!!" << endl;
                flag = !flag;
                break;
            default:
                cout << "\nPlease try again" << endl;
                break;
        }
    }

    cout << endl;
   
    return 0;
}