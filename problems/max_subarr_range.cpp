#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Node {
    public:
        int totalSum, maxSum;
        int prefixSum, suffixSum;

        Node(int ts = 0, int ms = 0, int bps = 0, int sss = 0) : totalSum(ts), maxSum(ms), prefixSum(bps), suffixSum(sss) {};
};

class SegTree {
    private:
        vector<int> arr;
        vector<Node> tree;

    public:
        // Initializes the segment tree
        SegTree(vector<int> &);

        // Builds a segment Tree via recursion
        void buildTree(int, int, int = 1);

        // Performs query on range
        Node query(int, int, int, int, int = 1);
};

SegTree :: SegTree(vector<int> &elems) {
    // We allocate four times the size of the given array
    // The actual size is 2 * pow(2, ceil(log2(arr.size()))) - 1
    tree.resize(4 * elems.size());
    arr = elems;

    // Recursively build the tree
    buildTree(0, arr.size() - 1);
}

void SegTree :: buildTree(int start, int end, int node) {
    // Base Condition, i.e. when start and end match, we
    // want to place the element at this node
    if (start == end) {
        tree[node] = Node(arr[start], arr[start], arr[start], arr[start]);
        return;
    }

    int mid = (end - start) / 2 + start;

    // For a complete binary tree, the children of a node are
    // present at 2 * curr for left & 2 * curr + 1 for right
    buildTree(start, mid, 2 * node);
    buildTree(mid + 1, end, 2 * node + 1);

    Node left = tree[2 * node];
    Node right = tree[2 * node + 1];

    Node curr;
    // For maximum sum of this node, we can have 5 possiblities
    // 1. Max Sum from left 2. Max Sum from right
    // 3. Max Suffix sum of left + Total sum of right
    // 4. Total sum of left + Max Prefix sum of right
    // 5. Max Suffix sum of left + Max Prefix sum of right
    curr.maxSum = max({left.maxSum, right.maxSum, left.totalSum + right.prefixSum, left.suffixSum + right.totalSum, left.suffixSum + right.prefixSum});
    // Total sum is simply their addition
    curr.totalSum = left.totalSum + right.totalSum;
    // Prefix sum for current is either the prefix sum
    // of left node or total sum of left + right prefix sum
    curr.prefixSum = max(left.prefixSum, left.totalSum + right.prefixSum);
    // Suffix sum for current is either suffix sum of right
    // or total sum of right + left suffix sum
    curr.suffixSum = max(right.suffixSum, left.suffixSum + left.totalSum);

    // We store the computed node at this place
    tree[node] = curr;
}

Node SegTree :: query(int left, int right, int start, int end, int node) {
    // Case when completely outiside given range
    if (left > end || right < start) return Node(INT16_MIN, INT16_MIN, INT16_MIN, INT16_MIN);

    // Case when completely inside range
    if (left <= start && right >= end) return tree[node];

    // Otherwise we will consider the range to be
    // partially present in both of its children
    int mid = (end - start) / 2 + start;
    Node part1 = query(left, right, start, mid, 2 * node);
    Node part2 = query(left, right, mid + 1, end, 2 * node + 1);

    Node result;
    result.maxSum = max({part1.maxSum, part2.maxSum, part1.totalSum + part2.prefixSum, part1.suffixSum + part2.totalSum, part1.suffixSum + part2.prefixSum});
    result.totalSum = part1.totalSum + part2.totalSum;
    result.prefixSum = max(part1.prefixSum, part1.totalSum + part2.prefixSum);
    result.suffixSum = max(part2.suffixSum, part1.suffixSum + part1.totalSum);

    return result;
}

int main() {
    /**
     * In order to find the maximum subarray sum continiously
     * within certain ranges, we will use a segment tree to 
     * store the maximum sum at each segments, and use it further
     */ 
    cout << "\nThis program finds maximum subarray sum within given ranges.\n" << endl;
    int n, q;
    cout << "Enter the size of the list to consider: ";
    cin >> n;
    cout << "Enter number of queries to consider: ";
    cin >> q;

    vector<int> arr(n);
    cout << "Enter space seperated elements of the array to consider," << endl;
    for (auto &x : arr) cin >> x;

    SegTree seg(arr);

    while (q--) {
        cout << "\nEnter space seperated starting & ending range," << endl;
        int start, end;
        cin >> start >> end;
        cout << "\nMaximum subarray sum between " << arr[start] << " and " << arr[end] << " is " << seg.query(start, end, 0, n - 1).maxSum << "." << endl;
    }

    cout << endl;

    return 0;
}