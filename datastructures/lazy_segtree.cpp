#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * Segment Tree is a data structure which is based on trees and
 * allows us range based queries in logarithmic time. However via
 * lazy propagation the changes are not implemented till query
 * thereby saving resoures on large operations
 */ 

class LazySegTree {
    private:
        vector<int> arr;
        vector<int> tree;
        vector<int> lazy;

    public:
        // Initializes the lazy segment tree
        LazySegTree(vector<int> &);

        // Builds a tree
        void buildTree(int, int, int = 1);

        // Updates any pending value in tree
        void lazyUpdate(int, int, int);

        // Performs lazy propagation
        void lazyPropagate(int, int, int, int);

        // Performs lazy updation on a range
        void update(int, int, int, int, int, int = 1);

        // Performs query on range
        int query(int, int, int, int, int = 1);
};

LazySegTree :: LazySegTree(vector<int> &elems) {
    // We allocate four times the size of the given array
    // The actual size is 2 * pow(2, ceil(log2(arr.size()))) - 1
    tree.resize(4 * elems.size(), 0);
    lazy.resize(4 * elems.size(), 0);
    arr = elems;

    // Recursively build the tree
    buildTree(0, arr.size() - 1);
}

void LazySegTree :: buildTree(int startingNode, int endingNode, int currNode) {
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

    // We store the minimal of subchildren at this node
    tree[currNode] = min(tree[2 * currNode], tree[2 * currNode + 1]);
}

void LazySegTree :: lazyUpdate(int currNode, int startingNode, int endingNode) {
    // No task is panding
    if (lazy[currNode] == 0) return;

    tree[currNode] += lazy[currNode];

    // We then simply propagate the changes
    lazyPropagate(currNode, lazy[currNode], startingNode, endingNode);

    // Reset current pending task after propagation
    lazy[currNode] = 0;
}

void LazySegTree :: lazyPropagate(int currNode, int value, int startingNode, int endingNode) {
    auto leftChild = 2 * currNode;
    auto rightChild = 2 * currNode + 1;

    // If this is not a leaf node, we will propagate
    // the changes to its subsequent nodes
    if (startingNode != endingNode) {
        lazy[leftChild] += value;
        lazy[rightChild] += value;
    }
}

void LazySegTree :: update(int leftRange, int rightRange, int increment, int startingNode, int endingNode, int currNode) {
    // Base Condition when range updation is complete
    if (startingNode > endingNode) return;

    // If there was a pending updateion remaining
    lazyUpdate(currNode, startingNode, endingNode);

    // Out of current node range
    if (endingNode < leftRange || rightRange < startingNode) return;

    // Complete overlapping of range within our selected node range
    if (leftRange <= startingNode && endingNode <= rightRange) {
        // We add the increment to current node
        tree[currNode] += increment;

        // For it's children we will simply propagate them for future
        lazyPropagate(currNode, increment, startingNode, endingNode);

        return;
    }

    // Partial Overlap, hence we need to find the sub overlaps
    int mid = (endingNode - startingNode) / 2 + startingNode;
    update(leftRange, rightRange, increment, startingNode, mid, 2 * currNode);
    update(leftRange, rightRange, increment, mid + 1, endingNode, 2 * currNode + 1);

    tree[currNode] = min(tree[currNode * 2], tree[currNode * 2 + 1]); 
}

int LazySegTree :: query(int left, int right, int startingNode, int endingNode, int currNode) {
    // Invalid Range
    if (startingNode > endingNode) return INT_MAX;

    // Case when completely outiside given range [S, E] < L || R < [S, E]
    if (endingNode < left || right < startingNode) return INT_MAX;

    // If there was a pending propagation remaining
    lazyUpdate(currNode, startingNode, endingNode);

    // Case when completely inside range L <= [S, E] <= R
    if (left <= startingNode && endingNode <= right) return tree[currNode];

    // Partial Overlapping of nodes
    int mid = (endingNode - startingNode) / 2 + startingNode;
    int part1 = query(left, right, startingNode, mid, 2 * currNode);
    int part2 = query(left, right, mid + 1, endingNode, 2 * currNode + 1);

    return min(part1, part2);
}

int main() {
    /**
     * We generate an instance of lazy segment tree class and perform operations
     */ 
    cout << "\nThis program generates a sample lazy segment tree object to find minimum in subarray.\n" << endl;
    int n;
    cout << "Enter number of elements to consider: ";
    cin >> n;

    vector<int> elems(n);
    cout << "Enter space seperated elements of the array to consider," << endl; 
    for (int i = 0; i < n; i += 1) cin >> elems[i];
    
    LazySegTree seg(elems);
    bool flag = true;

    while (flag) {
        cout << "\nEnter your choice:" << endl;
        cout << "1. Update range of elements of array." << endl;
        cout << "2. Query a specific range." << endl;
        cout << "3. Exit." << endl;
        int choice;
        cin >> choice;

        // Variables for choices
        int idx1, idx2, val;

        switch (choice) {
            case 1:
                cout << "\nEnter starting range: ";
                cin >> idx1;
                cout << "\nEnter ending range: ";
                cin >> idx2;
                cout << "\nEnter value to increment these elements by: ";
                cin >> val;
                seg.update(idx1, idx2, val, 0, n - 1);
                break;
            case 2:
                cout << "\nEnter starting range: ";
                cin >> idx1;
                cout << "\nEnter ending range: ";
                cin >> idx2;
                val = seg.query(idx1, idx2, 0, n - 1);
                cout << "\nThe minimum element from " << idx1 << " to " << idx2 << " is " << val << "." << endl;
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