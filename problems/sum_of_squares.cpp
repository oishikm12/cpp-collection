#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class TreeNode {
    // We use this structure in tree to store value of
    // sum of squares and the sum of all elements in range
    public:
    	int sum, sqsum;
    	TreeNode(int ss = 0, int s = 0) : sqsum(ss), sum(s) {};
};

class LazyNode {
    // We use this structure in lazy tree to store value
    // of updation & wether to increment or replace with it
    public:
    	int type, val;
    	LazyNode(int t = -1, int v = 0) : type(t), val(v) {};
};

class LazySegTree {
    private:
        vector<int> arr;
        vector<TreeNode> tree;
        vector<LazyNode> lazy;

    public:
        // Initializes the lazy segment tree
        LazySegTree(vector<int> &);

        // Builds a tree
        void buildTree(int, int, int = 1);
    
    	void propagate(int, int, int);

        // Performs lazy updation on a range
        void lazyUpdate(int, int, int, bool, int, int, int = 1);

        // Performs query on range
        TreeNode query(int, int, int, int, int = 1);
};

LazySegTree :: LazySegTree(vector<int> &elems) {
    // We aintocate four times the size of the given array
    // The actual size is 2 * pow(2, ceil(log2(arr.size()))) - 1
    tree.resize(4 * elems.size());
    lazy.resize(4 * elems.size());
    arr = elems;

    // Recursively build the tree
    buildTree(0, elems.size() - 1);
}

void LazySegTree :: buildTree(int startingNode, int endingNode, int currNode) {
    // Base Condition, i.e. when start and end match, we
    // want to place the element at this node
    if (startingNode == endingNode) {
        tree[currNode] = TreeNode(arr[startingNode] * arr[startingNode], arr[startingNode]);
        return;
    }

    int mid = (endingNode - startingNode) / 2 + startingNode;

    // For a complete binary tree, the children of a node are
    // present at 2 * curr for left & 2 * curr + 1 for right
    buildTree(startingNode, mid, 2 * currNode);
    buildTree(mid + 1, endingNode, 2 * currNode + 1);

    // We store the minimal of subchildren at this node
    auto left = tree[2 * currNode];
    auto right = tree[2 * currNode + 1];
    
    tree[currNode] = TreeNode(left.sqsum + right.sqsum, left.sum + right.sum);
}

void LazySegTree :: propagate(int currNode, int startingNode, int endingNode) {
    if (lazy[currNode].type == -1) return;
    
    if (lazy[currNode].type) {
        tree[currNode].sqsum += (lazy[currNode].val * lazy[currNode].val * (endingNode - startingNode + 1)) + (2 * lazy[currNode].val * tree[currNode].sum);
        tree[currNode].sum += lazy[currNode].val * (endingNode - startingNode + 1);

        // If this is not a leaf node, we will propagate
        // the changes to its subsequent nodes
        if (startingNode != endingNode) {
            // We would rather not change replacement with increment
            if (lazy[2 * currNode].type == -1) lazy[2 * currNode].type = true;
            if (lazy[2 * currNode + 1].type == -1) lazy[2 * currNode + 1].type = true;

            lazy[2 * currNode].val += lazy[currNode].val;
            lazy[2 * currNode + 1].val += lazy[currNode].val;
        }
    } else {
        tree[currNode].sqsum = (lazy[currNode].val * lazy[currNode].val * (endingNode - startingNode + 1));
        tree[currNode].sum = lazy[currNode].val * (endingNode - startingNode + 1);

        // If this is not a leaf node, we will propagate
        // the changes to its subsequent nodes
        if (startingNode != endingNode) {
            lazy[2 * currNode].type = lazy[2 * currNode + 1].type = false;
            lazy[2 * currNode].val = lazy[currNode].val;
            lazy[2 * currNode + 1].val = lazy[currNode].val;
        }
    }

    // Reset current pending task after propagation
    lazy[currNode].type = -1;
    lazy[currNode].val = 0;
}

void LazySegTree :: lazyUpdate(int leftRange, int rightRange, int increment, bool type, int startingNode, int endingNode, int currNode) {
    // Base Condition when range updation is complete
    if (startingNode > endingNode) return;

    // If there was a pending propagation remaining
    propagate(currNode, startingNode, endingNode);

    // Out of current node range
    if (endingNode < leftRange || rightRange < startingNode) return;

    // Complete overlapping of range within our selected node range
    if (leftRange <= startingNode && endingNode <= rightRange) {
        if (type) {
            tree[currNode].sqsum += (increment * increment * (endingNode - startingNode + 1)) + (2 * increment * tree[currNode].sum);
            tree[currNode].sum += increment * (endingNode - startingNode + 1);

            // If this is not a leaf node, we will propagate
            // the changes to its subsequent nodes
            if (startingNode != endingNode) {
                // We would rather not change replacement with increment
                if (lazy[2 * currNode].type == -1) lazy[2 * currNode].type = true;
                if (lazy[2 * currNode + 1].type == -1) lazy[2 * currNode + 1].type = true;

                lazy[2 * currNode + 1].val += increment;
            }
        } else {
            tree[currNode].sqsum = (increment * increment * (endingNode - startingNode + 1));
            tree[currNode].sum = increment * (endingNode - startingNode + 1);

            // If this is not a leaf node, we will propagate
            // the changes to its subsequent nodes
            if (startingNode != endingNode) {
                lazy[2 * currNode] = LazyNode(false, increment);
                lazy[2 * currNode + 1] = LazyNode(false, increment);
            }
        }
        return;
    }

    // Partial Overlap, hence we need to find the sub overlaps
    int mid = (endingNode - startingNode) / 2 + startingNode;
    lazyUpdate(leftRange, rightRange, increment, type, startingNode, mid, 2 * currNode);
    lazyUpdate(leftRange, rightRange, increment, type, mid + 1, endingNode, 2 * currNode + 1);

    tree[currNode] = TreeNode(tree[currNode * 2].sqsum + tree[currNode * 2 + 1].sqsum, tree[currNode * 2].sum + tree[currNode * 2 + 1].sum); 
}

TreeNode LazySegTree :: query(int left, int right, int startingNode, int endingNode, int currNode) {
    // Invalid Range
    if (startingNode > endingNode) return TreeNode();

    // Case when completely outiside given range [S, E] < L || R < [S, E]
    if (endingNode < left || right < startingNode) return TreeNode();

    // If there was a pending propagation remaining
    propagate(currNode, startingNode, endingNode);

    // Case when completely inside range L <= [S, E] <= R
    if (left <= startingNode && endingNode <= right) return tree[currNode];

    // Partial Overlapping of nodes
    int mid = (endingNode - startingNode) / 2 + startingNode;
    TreeNode part1 = query(left, right, startingNode, mid, 2 * currNode);
    TreeNode part2 = query(left, right, mid + 1, endingNode, 2 * currNode + 1);
    
    // cout << part1.sqsum << ' ' << part2.sqsum << ' '<< startingNode << ' ' << mid << ' ' << endingNode << endl;

    return TreeNode(part1.sqsum + part2.sqsum, part1.sum + part2.sum);
}


int main() {
    /**
     * In order to ensure updation in a ranged query we will
     * be use a lazy propagated segment tree, to perform 
     * updations & queries on demand via logarithmic time
     */ 
    cout << "\nThis program performs ranged updations & queries over a list of integers.\n" << endl;
    int n, q;
    cout << "Enter the size of the list to consider: ";
    cin >> n;
    cout << "Enter number of queries to consider: ";
    cin >> q;

    vector<int> arr(n);
    cout << "Enter space seperated elements of the array to consider," << endl;
    for (auto &x : arr) cin >> x;

    LazySegTree seg(arr);

    while (q--) {
        int type;
        cout << "\nEnter 0 for updation, 1 for query, followed by another 0 for increment updation, 1 for replace updation: ";
        cin >> type;
        cout << "\nEnter space seperated starting & ending range," << endl;
        int start, end;
        cin >> start >> end;

        if (type == 0) {
            int x, style;
            cout << "\nEnter the updation value: ";
            cin >> x;
            cout << "\nEnter 1 if to increment with this value, 0 if to replace: ";
            cin >> style;
            seg.lazyUpdate(start, end, x, style, 0, n - 1);
        } else {
            cout << "\nSum of squares between " << arr[start] << " and " << arr[end] << " is " << seg.query(start, end, 0, n - 1).sqsum << "." << endl;
        }       
    }

    cout << endl;

    return 0;
}