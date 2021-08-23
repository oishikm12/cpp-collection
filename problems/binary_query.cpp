#include <iostream>
#include <vector>
using namespace std;

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
        void updateTree(int, int, int, int = 1);

        // Performs query on range
        int query(int, int, int, int, int = 1);

        // Returns binary of a certain range
        string print(int, int);
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
    // When converting binary to decimal with two subsections, we
    // multiply decimal(left) * 2 + decimal(right) 
    int dist = endingNode - startingNode + 1;
    tree[currNode] = ((dist % 2 == 0 ? 1 : 2) * tree[2 * currNode] + tree[2 * currNode + 1]) % 3;
}

void SegTree :: updateTree(int index, int startingNode, int endingNode, int currNode) {
    // Invalid Range
    if (startingNode > endingNode) return;

    // Base Condition, i.e. when start and end match, we
    // want to replace this element itself
    if (startingNode == endingNode) {
        arr[index] = 1;
        tree[currNode] = 1;
        return;
    }

    int mid = (endingNode - startingNode) / 2 + startingNode;

    // If the index of element to update is greater
    // then we move to right subtree, i.e. 2 * n + 1
    // and if smaller then to left 2 * n itself
    if (index > mid) updateTree(index, mid + 1, endingNode, 2 * currNode + 1);
    else updateTree(index, startingNode, mid, 2 * currNode);

    // We store the sum of children nodes at current node
    int dist = endingNode - startingNode + 1;
    tree[currNode] = ((dist % 2 == 0 ? 1 : 2) * tree[2 * currNode] + tree[2 * currNode + 1]) % 3;
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

    int dist = endingNode - startingNode + 1;
    return ((dist % 2 == 0 ? 1 : 2) * part1 + part2) % 3;
}

string SegTree :: print(int start, int end) {
    string res;
    for (int i = start; i <= end; i += 1) res.push_back(arr[i] + '0');
    return res;
}

int main() {
    /**
     * In order to generate decimal value of certain range of
     * binary string, we will use a segment tree and store the
     * decimal value with 2 * left + right formulae
     */ 
    cout << "\nThis program returns decimal value of a given binary subsequence.\n" << endl;
    int n, q;
    cout << "Enter the size of the binary string to consider: ";
    cin >> n;
    cout << "Enter number of queries to consider: ";
    cin >> q;

    vector<int> arr(n);
    cout << "Enter space seperated elements of the binary literal," << endl;
    for (auto &x : arr) cin >> x;

    SegTree seg(arr);

    while (q--) {
        int type;
        cout << "\nEnter type of query, 0 for updating a bit, 1 for printing a range: ";
        cin >> type;

        if (type == 0) {
            int idx;
            cout << "\nEnter index of bit to switch to 1: ";
            cin >> idx;
            seg.updateTree(idx, 0, n - 1);
        } else {
            cout << "\nEnter space seperated starting & ending range," << endl;
            int start, end;
            cin >> start >> end;
            cout << "\nDecimal value of " << seg.print(start, end) << " modulo 3 is " << seg.query(start, end, 0, n - 1) << "." << endl;
        }
    }

    cout << endl;

    return 0;
}